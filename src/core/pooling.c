#include "maze_c/pooling.h"

#include "maze_c/utils.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 맵 축소 후 크기 추정하기
 *
 * @param original_map_size 기존 맵 사이즈 (한 변)
 *
 * @return reduced_map_size 추정된 축소 후 맵 크기
 */
int estimate_reduce_map_size(int original_map_size) {
  // 테스트 결과 (11/82) 비율로 해야 적당하였음
  const double REDUCTION_RATIO = 11.0 / 82.0;

  int reduced_map_size =
      (int)(((double)original_map_size * REDUCTION_RATIO) + 0.5);

  if (reduced_map_size < 10) {
    return -1;
  }
  return reduced_map_size;
}

// 손실 없는 풀링을 위한 matrix 크기 구하기
static int get_block_sizes(int *out_block_list, int original_size,
                           int target_size) {
  if (target_size <= 0) {
    return -1;
  }
  int quotient = original_size / target_size;
  int remainder = original_size % target_size;

  for (int i = 0; i < target_size; i++) {
    if (i < remainder) {
      out_block_list[i] = quotient + 1;
    } else {
      out_block_list[i] = quotient;
    }
  }
  return 0;
}

// 풀링 적용
static int pooling(int **map, int **out_reduced_map, int original_size,
                   int target_size) {
  int *block_size_list = create_int_arr(target_size);
  if (block_size_list == NULL) {
    return -1;
  }

  get_block_sizes(block_size_list, original_size, target_size);

  int *row_start = create_int_arr(target_size + 1);
  if (row_start == NULL) {
    return -1;
  }
  int *col_start = create_int_arr(target_size + 1);
  if (col_start == NULL) {
    return -1;
  }

  row_start[0] = 0;
  col_start[0] = 0;

  for (int i = 0; i < target_size; i++) {
    row_start[i + 1] = row_start[i] + block_size_list[i];
    col_start[i + 1] = col_start[i] + block_size_list[i];
  }

  for (int row = 0; row < target_size; row++) {
    for (int col = 0; col < target_size; col++) {
      int max = 0;
      for (int r = row_start[row]; r < row_start[row + 1]; r++) {
        for (int c = col_start[col]; c < col_start[col + 1]; c++) {
          if (map[r][c] > max) {
            max = map[r][c];
          }
        }
      }
      out_reduced_map[row][col] = max;
    }
  }

  free(row_start);
  free(col_start);
  free(block_size_list);
  return 0;
}

// 입출구 찾기
static int find_gateway_index(int **map, int size) {
  int center_col_index = size / 2;

  if (map[0][center_col_index] == 0 && map[size - 1][center_col_index] == 0) {
    return center_col_index;
  }

  for (int offset = 1; offset <= center_col_index; offset++) {
    int left = center_col_index - offset;
    int right = center_col_index + offset;

    if (left >= 0 && map[0][left] == 0) {
      if (map[0][left] == 0 && map[size - 1][left] == 0) {
        return left;
      }
    }
    if (right < size && map[0][right] == 0) {
      if (map[0][right] == 0 && map[size - 1][right] == 0) {
        return right;
      }
    }
  }
  // 0이 없으면 강제 선택
  return center_col_index;
}

// 최외곽이 0인 버그 처리, 최외곽을 1(벽)으로 하고 입출구 뚫기
static int close_map_boundaries_bug(int **map, int size) {
  for (int row = 0; row < size; row++) { // 세로 평행 줄
    map[row][0] = 1;
    map[row][size - 1] = 1;
  }
  for (int col = 0; col < size; col++) {
    map[0][col] = 1;
    map[size - 1][col] = 1;
  }

  int gateway_index = find_gateway_index(map, size);
  if (gateway_index < 0 || gateway_index >= size) {
    fprintf(stderr, "[ERROR] 게이트웨이 인덱스 오류 (index: %d)\n",
            gateway_index);
    return -1;
  }

  map[0][gateway_index] = 0;
  map[size - 1][gateway_index] = 0;
  return 0;
}

/**
 * @brief 맵 축소 알고리즘
 *
 * 맵을 최대한 손실 없이 축소시키는 알고리즘
 *
 * @param map 기존 크기 맵
 * @param out_reduced_map 축소 후 맵
 * @param height 행 사이즈
 * @param width 열 사이즈
 * @param reduced_map_size 축소 크기 (estimate_reduce_map_size() 함수 리턴 값)
 */
int apply_reduce_map(int **map, int **out_reduced_map, int height, int width,
                     int reduced_map_size) {
  if (width != height) { // 일단은 정사각형으로 가정
    fprintf(stderr, "[ERROR] 맵이 정사각형이 아닙니다");
    return -1;
  }

  printf("[INFO] 원본 ( %d * %d )에서 ( %d * %d )로 축소됩니다.\n", width,
         height, reduced_map_size, reduced_map_size);
  if (pooling(map, out_reduced_map, width, reduced_map_size) == !0) {
    fprintf(stderr, "[ERROR] Pooling 실패\n");
    return -1;
  }
  if (close_map_boundaries_bug(out_reduced_map, reduced_map_size) != 0) {
    fprintf(stderr, "[ERROR] 맵 경계 처리 실패");
    return -1;
  }

  return 0;
}