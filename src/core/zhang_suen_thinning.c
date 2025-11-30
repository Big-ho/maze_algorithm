#include "maze_c/thinning.h"

#include "maze_c/utils.h"
#include <string.h>

// 이웃픽셀 주소 관리용
const int DELTA_ROW[NEIGHBOR_PIXEL_SIZE] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int DELTA_COL[NEIGHBOR_PIXEL_SIZE] = {0, 1, 1, 1, 0, -1, -1, -1};

// 검사할 픽셀의 이웃픽셀 가져오기
static int get_neighbor_pixels(int **map, int row, int col,
                               int out_p[NEIGHBOR_PIXEL_SIZE]) {
  if (map == NULL || out_p == NULL) {
    return -1;
  }

  for (int i = 0; i < NEIGHBOR_PIXEL_SIZE; i++) {
    int neighbor_row = row + DELTA_ROW[i];
    int neighbor_col = col + DELTA_COL[i];

    out_p[i] = map[neighbor_row][neighbor_col];
  }
  return 0;
}

/* 아래 get_condition_a_b 통일화
int condition_a(const int *p) {
  int count = 0;
  for (int i = 0; i < NEIGHBOR_PIXEL_SIZE; i++) {
    if (p[i] == BACKGORUND_VALUE &&
        (p[i + 1] % NEIGHBOR_PIXEL_SIZE) == OBJECT_VALUE) {
      count++;
    }
  }
  return count;
}

int condition_b(const int *p) {
  int sum = 0;
  for (int i = 0; i < NEIGHBOR_PIXEL_SIZE; i++) {
    sum += p[i];
  }
  return sum;
}
*/

// 조건 a, b 가져오기
static int get_condition_a_b(const int *p, int *out_count, int *out_sum) {
  int count = 0;
  int sum = 0;

  for (int i = 0; i < NEIGHBOR_PIXEL_SIZE; i++) {
    int curr = p[i];
    int next = p[(i + 1) % NEIGHBOR_PIXEL_SIZE];
    if (curr == BACKGORUND_VALUE && next == OBJECT_VALUE) {
      count++;
    }
    sum += curr;
  }

  if (out_count) {
    *out_count = count;
  }
  if (out_sum) {
    *out_sum = sum;
  }
  return 0;
}

// 세선화 알고리즘 조건을 적용하여 지울 픽셀인지 확인하기
static int is_delete_pixel(const int *p, ThinningStep step) {
  int condition_a_count = 0;
  int condition_b_sum = 0;
  get_condition_a_b(p, &condition_a_count, &condition_b_sum);

  if (condition_a_count != 1) {
    return 0;
  }
  if (condition_b_sum < 2 || condition_b_sum > 6) {
    return 0;
  }

  int p2 = p[0];
  int p4 = p[2];
  int p6 = p[4];
  int p8 = p[6];
  if (step == THINNING_STEP_1) { // Step 1
    if (p2 * p4 * p6 != 0) {
      return 0;
    }
    if (p4 * p6 * p8 != 0) {
      return 0;
    }

  } else if (step == THINNING_STEP_2) { // Step 2
    if (p2 * p4 * p8 != 0) {
      return 0;
    }
    if (p2 * p6 * p8 != 0) {
      return 0;
    }
  }
  return 1;
}

// 지울 픽셀 마킹하기
static int mark_delete_pixels(int **map, int **out_marker, int height,
                              int width, ThinningStep step) {
  if (map == NULL || out_marker == NULL) {
    return -1;
  }

  memset(out_marker[0], 0, (size_t)height * width * sizeof(int));
  for (int row = 1; row < height - 1; row++) {
    for (int col = 1; col < width - 1; col++) {
      if (map[row][col] == BACKGORUND_VALUE) {
        continue;
      }
      int p[NEIGHBOR_PIXEL_SIZE] = {0};
      get_neighbor_pixels(map, row, col, p);

      if (is_delete_pixel(p, step)) {
        out_marker[row][col] = OBJECT_VALUE;
      }
    }
  }
  return 0;
}

// 2차원 배열 안에 0이 아닌 것들 개수 반환
static int count_non_zero(int **map, int height, int width) {
  if (map == NULL) {
    return 0;
  }

  int count = 0;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      if (map[row][col] != 0) {
        count++;
      }
    }
  }
  return count;
}

// 지울 픽셀을 실질적으로 지우기
static int is_apply_delete_pixels(int **out_map, int **marker, int height,
                                  int width, ThinningStep step) {
  mark_delete_pixels(out_map, marker, height, width, step);

  if (count_non_zero(marker, height, width) == 0) {
    return 0;
  }
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      if (marker[row][col]) {
        out_map[row][col] = BACKGORUND_VALUE;
      }
    }
  }
  return 1;
}

/**
 * @brief ZhangSuen 세선화 알고리즘
 *
 * 선의 두께를 1로 바꾸는 알고리즘
 * https://rosettacode.org/wiki/Zhang-Suen_thinning_algorithm
 *
 * @param out_map 수정할 맵
 * @param height 행 사이즈
 * @param width 열 사이즈
 */
int zhang_suen_thinning(int **out_map, int width, int height) {
  if (out_map == NULL) {
    return -1;
  }

  int is_runing = 1;
  int **marker = create_2d_array(width, height);

  while (is_runing) {
    is_runing = 0;

    // Step 1
    if (is_apply_delete_pixels(out_map, marker, height, width,
                               THINNING_STEP_1)) {
      is_runing = 1;
    }

    // Step 2
    if (is_apply_delete_pixels(out_map, marker, height, width,
                               THINNING_STEP_2)) {
      is_runing = 1;
    }
  }
  free_2d_array(marker);

  return 0;
}