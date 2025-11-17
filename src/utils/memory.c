#include "maze_c/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// (int)형 동적 메모리 할당 함수
int *create_int_arr(int size) {
  int *arr = malloc(size * sizeof(int));
  if (arr == NULL) {
    perror("[ERROR] 메모리 할당 실패");
    return NULL;
  }
  return arr;
}

// (int)형 2차원 동적 메모리 할당 함수
int **create_2d_array(int height, int width) {
  int **arr = (int **)malloc(height * sizeof(int *));
  if (arr == NULL) {
    perror("[ERROR] 메모리 할당 실패 (행)");
    return NULL;
  }

  int *data = (int *)calloc((size_t)height * width, sizeof(int));
  if (data == NULL) {
    perror("[ERROR] 메모리 할당 실패 (열)");
    free(arr);
    return NULL;
  }

  for (int i = 0; i < height; i++) {
    arr[i] = data + ((size_t)i * width);
  }
  return arr; // NOLINT(clang-analyzer-unix.Malloc)
}

// (int)형 2차원 동적 메모리 해제 함수
void free_2d_array(int **arr) {
  if (arr == NULL) {
    return;
  }
  if (arr[0] != NULL) {
    free(arr[0]);
  }
  free(arr);
}