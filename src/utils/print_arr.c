#include "maze_c/types.h"
#include <stdio.h>

// 테스트용 출력 유틸
void print_2d_array(int **arr, int height, int width) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  printf("\n=======================================================\n");
}

void print_rgb_array(ColorRGB **arr, int height, int width) {
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < height; col++) {
      printf("(%d %d %d) ", arr[row][col].red, arr[row][col].green,
             arr[row][col].blue);
    }
    printf("\n");
  }
  printf("\n=======================================================\n");
}