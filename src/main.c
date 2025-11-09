#include "core.h"
#include "utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  const char *filename = "asset/map.txt";
  int rows;
  int cols;
  int **map = load_map(filename, &rows, &cols);

  if (map == NULL) {
    fprintf(stderr, "[ERROR] 맵 읽기 실패⚠️");
    return 1;
  }

  display_2d_map(map, rows, cols);

  for (int i = 0; i < rows; i++) {
    free(map[i]);
  }
  free(map);

  return 0;
}
