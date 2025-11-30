#pragma once

#include "maze_c/types.h"

int get_dynamic_tracker_delay(Point p1, Point p2, int base);
void display_map(Map map);
void render();
int process_input(Map *map, int key);
int is_clear(Map map);
int is_gameover(Map map);