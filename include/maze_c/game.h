#pragma once

#include "maze_c/types.h"

int get_dynamic_tracker_delay(int distance, int base_delay);
void display_map(Map map);
void render();
int process_input(Map *map, int key);
int is_clear(Map map);
int is_gameover(Map map);