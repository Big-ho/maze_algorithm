#pragma once

#include "maze_c/types.h"

ColorRGB **load_bmp(const char *filename, int *out_width, int *out_height);
void free_bmp(ColorRGB **img);
ColorRGB **create_bmp(int height, int width);