#pragma once

#include "stddef.h"

// 주요 상수 값 (가독성 & 유지보수 측면)
enum {
  NEIGHBOR_PIXEL_SIZE = 8,
  BACKGORUND_VALUE = 0,
  OBJECT_VALUE = 1,
  MAX_PIXEL_COLOR = 255,
};

// step 타입 선언 (가독성 측면)
typedef enum {
  THINNING_STEP_1 = 0,
  THINNING_STEP_2 = 1,
} thinning_step_t;

extern const int DELTA_ROW[NEIGHBOR_PIXEL_SIZE];
extern const int DELTA_COL[NEIGHBOR_PIXEL_SIZE];

int zhang_suen_thinning(int **out_map, int hight, int width);