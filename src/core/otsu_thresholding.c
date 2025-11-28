#include "maze_c/image_reader.h"
#include "maze_c/thresholding.h"
#include "stddef.h"

static unsigned char to_grayscale(rgb_quad_t pixel) {
  // 그레이스케일 변환
  int gray = (pixel.red * RED_WEIGHT + pixel.green * GREEN_WEIGHT +
              pixel.blue * BLUE_WEIGHT) /
             1000;

  if (gray > 255) {
    return 255;
  }
  if (gray < 0) {
    return 0;
  }
  return (unsigned char)gray;
}

static void create_histogram(rgb_quad_t **img, int *out_hist, int height,
                             int width) {
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      unsigned char gray = to_grayscale(img[row][col]);
      out_hist[gray]++;
    }
  }
};

static int find_threshold(const int *hist, int height, int width) {
  int total_pixels = height * width;

  // 변수명 참고 br = brightness
  float sum_total_br = 0;
  for (int i = 0; i < 256; i++) {
    sum_total_br += (float)(i * hist[i]);
  }

  float sum_background_br = 0;
  int count_background_br = 0;
  int count_foreground_br = 0;

  float max_variance = 0.0F;
  int optimal_threshold = 0;

  for (int k = 0; k < 256; k++) {
    count_background_br += hist[k];
    if (count_background_br == 0) {
      continue;
    }

    count_foreground_br = total_pixels - count_background_br;
    if (count_foreground_br == 0) {
      break;
    }

    sum_background_br += (float)(k * hist[k]);

    float mean_background_br = sum_background_br / (float)count_background_br;
    float mean_foreground_br =
        (sum_total_br - sum_background_br) / (float)count_foreground_br;

    float variance = (float)(count_background_br * count_foreground_br) *
                     (mean_background_br - mean_foreground_br) *
                     (mean_background_br - mean_foreground_br);

    if (variance > max_variance) {
      max_variance = variance;
      optimal_threshold = k;
    }
  }

  return optimal_threshold;
}

int otsu_thresholding(rgb_quad_t **img, int **out_binary_map, int height,
                      int width) {
  if (img == NULL || height <= 0 || width <= 0) {
    return -1;
  }

  // 히스토그램 생성
  int hist[256] = {0};
  create_histogram(img, hist, height, width);

  // 임계값 찾기
  int optimal_threshold = find_threshold(hist, height, width);

  // 이진화 적용
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      unsigned char gray = to_grayscale(img[row][col]);
      unsigned char binary = (gray > optimal_threshold) ? 0 : 1;

      out_binary_map[row][col] = binary;
    }
  }

  // 계산된 임계값 반환
  return optimal_threshold;
};