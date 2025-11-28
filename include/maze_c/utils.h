#pragma once

#include "maze_c/image_reader.h"

// --- terminal ---
void init_term(void);
void reset_term(void);
int kbhit(void);
void sleep_ms(int ms);

// --- utils ---
enum { // 최대 맵 크기, 최소 맵 크기
  MAX_MAP_DIMENSION = 512,
  MIN_MAP_DIMENSION = 5,
};
int print_2d_array(int **arr, int height, int width);
void print_rgb_array(rgb_quad_t **arr, int height, int width);
int **load_map_to_create_2darray(const char *filename, int *out_height,
                                 int *out_width);

// --- memory ---
int *create_int_arr(int size);
int **create_2d_array(int height, int width);
void free_2d_array(int **arr);
