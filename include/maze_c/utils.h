#pragma once

#include "maze_c/types.h"

// --- terminal ---
void init_term(void);
void reset_term(void);
int kbhit(void);
void sleep_ms(int ms);

// --- selelct_menu ---
void display_menu(const char *list[], int list_size);
int select_menu(int max);
void buffer_clear();

// --- memory ---
int *create_int_arr(int size);
int **create_2d_array(int width, int height);
void free_2d_array(int **arr);

// ===========================================

// --- print_arr (test utils) ---
int print_2d_array(int **arr, int height, int width);
void print_rgb_array(ColorRGB **arr, int height, int width);

// --- load_file (test utils) ---
int **load_map_to_create_2darray(const char *filename, int *out_height,
                                 int *out_width);