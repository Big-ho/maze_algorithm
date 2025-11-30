#include "maze_c/utils.h"

#include <stddef.h>
#include <stdio.h>

/**
 * @brief txt 파일에서 맵 데이터를 읽어서 2차원 배열로 반환
 *
 * @param filename 읽을 파일 주소
 * @param out_height 행 사이즈
 * @param out_width 열 사이즈
 *
 * @return int** 2차원 배열
 */
int **load_map_to_create_2darray(const char *filename, int *out_height,
                                 int *out_width) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("파일을 열 수 없습니다");
    return NULL;
  }

  int rows = 0;
  int cols = 0;
  if (fscanf(f, "Rows: %d, Cols: %d", &rows, &cols) != 2) {
    fprintf(stderr, "[ERROR] 파일 형식 오류 (Rows/Cols)\n");
    fclose(f);
    return NULL;
  }

  int **map = create_2d_array(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int val;
      // 파일 끝, 형식 오류 체크
      if (fscanf(f, "%d", &val) != 1) {
        fprintf(stderr, "[ERROR] 맵 데이터 읽기 오류\n");
        free_2d_array(map);
        fclose(f);
        return NULL;
      }
      map[i][j] = val;
    }
  }
  *out_height = rows;
  *out_width = cols;
  fclose(f);
  return map;
}