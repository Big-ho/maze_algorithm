#pragma once

#include "maze_c/image_reader.h"

enum {
  RED_WEIGHT = 299,
  GREEN_WEIGHT = 587,
  BLUE_WEIGHT = 114,
};

int otsu_thresholding(rgb_quad_t **img, int **out_binary_map, int height,
                      int width);