#include <stdio.h>

void display_2d_map(int **map, int row_size, int col_size) {
  for (int row = 0; row < row_size; row++) {
    for (int col = 0; col < col_size; col++) {
      if (map[row][col] == 1) {
        printf("■");
      } else {
        printf("\033[30m■\033[0m");
      }
    }
    putchar('\n');
  }
}