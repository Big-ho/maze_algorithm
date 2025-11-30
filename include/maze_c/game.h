#pragma once

#include "maze_c/types.h"

void display_map(Map map);
void render();
int process_input(Map *map, int key);
int is_clear(Map map);