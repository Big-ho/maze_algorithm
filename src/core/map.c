#include "maze_c/map.h"

#include "maze_c/image_reader.h"
#include "maze_c/pooling.h"
#include "maze_c/thinning.h"
#include "maze_c/thresholding.h"
#include "maze_c/types.h"
#include "maze_c/utils.h"

#include <stddef.h>
#include <stdio.h>

static int find_gate(const int *row, int width) {
  int start_col = -1;
  int end_col = -1;

  for (int col = 0; col < width; col++) {
    if (row[col] == 0) { // 길
      if (start_col == -1) {
        start_col = col;
      }
      end_col = col;
    } else { // 벽
      if (start_col != -1) {
        break;
      }
    }
  }
  if (start_col == -1) { // 문 없음
    return -1;
  }

  return (start_col + end_col) / 2;
}

void free_map(Map *out_map) {
  if (out_map == NULL) {
    return;
  }

  if (out_map->grid != NULL) {
    free_2d_array(out_map->grid);
  }
}

void reset_map(Map *out_map) {
  free_map(out_map);
  out_map->grid = NULL;
  out_map->width = 0;
  out_map->height = 0;

  Point reset = {-1, -1};

  out_map->player = reset;
  out_map->tracker = reset;
  out_map->start = reset;
  out_map->exit = reset;
}

int init_custom_map(Map *out_map, char *filepath) {
  int origin_w = 0;
  int origin_h = 0;

  ColorRGB **bmp = load_bmp(filepath, &origin_w, &origin_h);
  if (bmp == NULL) {
    fprintf(stderr, "[ERROR] 이미지 로드 실패⚠️\n");
    return -1;
  }

  int **binary = create_2d_array(origin_w, origin_h);
  otsu_thresholding(bmp, binary, origin_w, origin_h);
  free_bmp(bmp);

  zhang_suen_thinning(binary, origin_w, origin_h);

  int reduced_map_size = estimate_reduce_map_size(origin_h);
  if (reduced_map_size < 0) {
    fprintf(stderr, "[ERROR] 맵 생성 실패 (크기 오류)⚠️\n");
    free_2d_array(binary);
    return -1;
  }

  int **reduced_map = create_2d_array(reduced_map_size, reduced_map_size);
  apply_reduce_map(binary, reduced_map, origin_w, origin_h, reduced_map_size);
  free_2d_array(binary);

  out_map->grid = reduced_map;
  out_map->width = reduced_map_size;
  out_map->height = reduced_map_size;

  int start = find_gate(out_map->grid[out_map->height - 1], out_map->width);
  int exit = find_gate(out_map->grid[0], out_map->width);

  if (start == -1 || exit == -1) {
    fprintf(stderr, "[ERROR] 입출구 찾기 실패⚠️\n");
    return -1;
  }

  out_map->start = (Point){start, out_map->height - 1};
  out_map->exit = (Point){exit, 0};
  out_map->player = out_map->start;
  out_map->tracker = out_map->start;

  return 0;
}