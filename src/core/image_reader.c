#include "maze_c/image_reader.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

rgb_quad_t **create_bmp(int height, int width) {
  rgb_quad_t **img = malloc(height * sizeof(rgb_quad_t *));
  if (img == NULL) {
    perror("[ERROR] 이미지 메모리 할당 실패 (행)\n");
    return NULL;
  }

  rgb_quad_t *data = calloc((size_t)height * width, sizeof(rgb_quad_t));
  if (data == NULL) {
    perror("[ERROR] 이미지 메모리 할당 실패 (열)\n");
    free(img);
    return NULL;
  }
  for (int i = 0; i < height; i++) {
    img[i] = data + ((size_t)i * width);
  }

  return img; // NOLINT(clang-analyzer-unix.Malloc)
}

void free_bmp(rgb_quad_t **img, int height) {
  if (img == NULL) {
    return;
  }

  if (img[0] != NULL) {
    free(img[0]);
  }
  free(img);
}

rgb_quad_t **load_bmp(const char *filename, int *height, int *width) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror("bmp 파일을 열 수 없습니다\n");
    return NULL;
  }

  bitmap_file_header_t file_header;
  bitmap_info_header_t info_header;

  if (fread(&file_header, sizeof file_header, 1, f) != 1 ||
      fread(&info_header, sizeof info_header, 1, f) != 1) {
    fprintf(stderr, "[ERROR] 헤더 읽기 실패\n");
    fclose(f);
    return NULL;
  };

  if (file_header.bf_type != 0x4D42 && file_header.bf_type != 0x424D ||
      info_header.bi_bit_count != 32) {
    fclose(f);
    fprintf(stderr, "[ERROR] BMP 포맷 에러, 타입: %d 비트: %d\n",
            file_header.bf_type, info_header.bi_bit_count);
    return NULL;
  }

  *width = info_header.bi_width;
  *height = abs(info_header.bi_height);

  rgb_quad_t **img = create_bmp(*height, *width);
  if (img == NULL) {
    fprintf(stderr, "[ERROR] 메모리 할당 실패\n");
    fclose(f);
    return NULL;
  }

  fseek(f, file_header.bf_offbits, SEEK_SET);

  int padding = (4 - (*width * 3) % 4) % 4;

  unsigned char pixel_buf[3];

  for (int row = *height - 1; row >= 0; row--) {
    if (row < 0 || row >= *height) {
      break;
    }
    for (int col = 0; col < *width; col++) {
      if (col < 0 || col >= *width) {
        break;
      }
      if (fread(pixel_buf, 1, 3, f) != 3) {
        break;
      }

      // NOLINTNEXTLINE(clang-analyzer-security.ArrayBound)
      img[row][col].blue = pixel_buf[0];
      img[row][col].green = pixel_buf[1];
      img[row][col].red = pixel_buf[2];
      img[row][col].reserved = 0;
    }
    fseek(f, padding, SEEK_CUR);
  }

  fclose(f);
  return img;
}