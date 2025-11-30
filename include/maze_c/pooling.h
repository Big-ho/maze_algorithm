#pragma once

int estimate_reduce_map_size(int original_map_size);
int apply_reduce_map(int **map, int **out_reduced_map, int width, int height,
                     int reduced_map_size);