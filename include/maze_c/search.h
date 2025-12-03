#pragma once

#include "maze_c/types.h"

int **bfs(const Map *map);
Point get_next_step(int **dist, Point *p, int w, int h);
