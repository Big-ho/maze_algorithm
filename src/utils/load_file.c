#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief txt 파일에서 맵 데이터를 읽어서 2차원 배열로 반환
 *
 * @param filename 읽을 파일 주소
 * @param rows_out 행 사이즈 (포인터 반환)
 * @param cols_out 열 사이즈 (포인터 반환)
 * @return int** 2차원 배열
 */
int **load_map(const char *filename, int *rows_out, int *cols_out) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("파일을 열 수 없습니다");
    return NULL;
  }

  int row_size = 0;
  int col_size = 0;
  if (fscanf(f, "Rows: %d, Cols: %d", &row_size, &col_size) != 2) {
    fprintf(stderr, "[ERROR] 파일 형식 오류 (Rows/Cols)\n");
    fclose(f);
    return NULL;
  }

  *rows_out = row_size;
  *cols_out = col_size;

  int **map = malloc(sizeof(int *) * row_size);
  if (map == NULL) {
    perror("[ERROR] 메모리 할당 실패 (행)");
    fclose(f);
    return NULL;
  }

  for (int i = 0; i < row_size; i++) {
    map[i] = malloc(sizeof(int) * col_size);
    if (map[i] == NULL) {
      perror("[ERROR] 메모리 할당 실패 (열)");
      for (int k = 0; k < i; k++) {
        free(map[k]);
      }
      free(map);
      fclose(f);
      return NULL;
    }

    for (int j = 0; j < col_size; j++) {
      int val;
      // 파일 끝, 형식 오류 체크
      if (fscanf(f, "%d", &val) != 1) {
        fprintf(stderr, "[ERROR] 맵 데이터 읽기 오류\n");
        for (int k = 0; k <= i; k++) { // 'i'번째 행 포함
          free(map[k]);
        }
        free(map);
        fclose(f);
        return NULL;
      }
      map[i][j] = val;
    }
  }

  fclose(f);

  return map;
}