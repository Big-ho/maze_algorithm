#pragma once

#include "maze_c/types.h"

#define MAX_MAP_SIZE 1000

int init_custom_map(Map *out_map, char *filepath);
void free_map(Map *map);
void reset_map(Map *map);