#include <stdio.h>

// 테스트용 출력 유틸
void display_2d_array(int **arr, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  printf("\n=======================================================\n");
}