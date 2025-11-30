#pragma once

#include "maze_c/types.h"

enum {
  RED_WEIGHT = 299,
  GREEN_WEIGHT = 587,
  BLUE_WEIGHT = 114,
};

int otsu_thresholding(ColorRGB **img, int **out_binary_map, int width,
                      int height);