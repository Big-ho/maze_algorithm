#include "maze_c/game.h"

#include "maze_c/types.h"

#include <stdio.h>

int get_dynamic_tracker_delay(int distance, int base_delay) {
  if (distance < 5) {
    return base_delay * 2;
  }
  if (distance < 15) {
    return base_delay;
  }
  if (distance < 30) {
    return (int)(base_delay * 0.7);
  }

  return base_delay / 2;
}

void display_map(Map map) {
  for (int row = 0; row < map.height; row++) {
    for (int col = 0; col < map.width; col++) {
      if (col == map.player.x && row == map.player.y) { // 플레이어
        printf("O");
      } else if (col == map.tracker.x && row == map.tracker.y) { // 추격자
        printf("X");
      } else if (map.grid[row][col] == 1) { // 벽
        printf("#");
      } else if (col == map.exit.x && row == map.exit.y) { // 추격자
        printf("E");
      } else {
        printf(" ");
      }
    }
    putchar('\n');
  }
}

void render() { printf("\033[H\033[J"); }

int process_input(Map *map, int key) {
  if (key == 113 || key == 81) { // q
    return 1;                    // 종료
  }
  int nx = map->player.x;
  int ny = map->player.y;

  if (key == 119 || key == 87) {
    ny -= 1; // 위
  } else if (key == 97 || key == 65) {
    nx -= 1; // 왼
  } else if (key == 115 || key == 83) {
    ny += 1; // 아
  } else if (key == 100 || key == 68) {
    nx += 1; // 오
  }

  if (nx < 0 || nx >= map->width || ny < 0 || ny >= map->height) {
    return 0;
  }

  if (map->grid[ny][nx] != 1) {
    map->player.x = nx;
    map->player.y = ny;
  }

  return 0;
}

int is_clear(Map map) {
  return map.player.x == map.exit.x && map.player.y == map.exit.y;
}

int is_gameover(Map map) {
  return map.player.x == map.tracker.x && map.player.y == map.tracker.y;
}