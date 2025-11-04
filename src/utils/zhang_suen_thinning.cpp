#include "utils/zhang_suen_thinning.hpp"

#include <array>
#include <numeric>

auto GetNeighborsPixels(const cv::Mat& img, int row, int col,
                        std::array<uchar, kNeighborsPixelsSize>& p) -> void {
  // p[n]값은 3x3에서 p1(2,2), p2(1,2), p3(1,3) ... p1 중심 시계 방향
  const std::array<int, kNeighborsPixelsSize> kDeletaRow = {-1, -1, 0, 1, 1, 1, 0, -1};
  const std::array<int, kNeighborsPixelsSize> kDeletaCol = {0, 1, 1, 1, 0, -1, -1, -1};

  // index[0]~index[7] -> p2~p9
  // (row, col)이 중심 p1
  for (int i = 0; i < kNeighborsPixelsSize; i++) {
    int neighbor_row = row + kDeletaRow.at(i);
    int neighbor_col = col + kDeletaCol.at(i);

    p.at(i) = img.at<uchar>(neighbor_row, neighbor_col);
  }
}

auto CountConditionA(const std::array<uchar, kNeighborsPixelsSize>& p) -> int {
  int condition_a_count = 0;
  for (int i = 0; i < kNeighborsPixelsSize; i++) {
    if (p.at(i) == kBackgroundValue && (p.at((i + 1) % kNeighborsPixelsSize) == kThinningValue)) {
      condition_a_count++;
    }
  }

  return condition_a_count;
}

auto CalculateConditionB(const std::array<uchar, kNeighborsPixelsSize>& p) -> int {
  return std::accumulate(p.begin(), p.end(), 0);
}

auto ShouldMarkPixel(const std::array<uchar, kNeighborsPixelsSize>& p, int step) -> bool {
  int condition_a = CountConditionA(p);
  int condition_b = CalculateConditionB(p);

  if (condition_a != 1) {
    return false;
  }
  if (condition_b < 2 || condition_b > kMagicNumberSix) {
    return false;
  }

  int p2 = p[static_cast<int>(NeighborsIndexs::kP2)];
  int p4 = p[static_cast<int>(NeighborsIndexs::kP4)];
  int p6 = p[static_cast<int>(NeighborsIndexs::kP6)];
  int p8 = p[static_cast<int>(NeighborsIndexs::kP8)];

  if (step == 0) {  // Step 1
    if (p2 * p4 * p6 != 0) {
      return false;
    }
    if (p4 * p6 * p8 != 0) {
      return false;
    }
  } else {  // Step 2
    if (p2 * p4 * p8 != 0) {
      return false;
    }
    if (p2 * p6 * p8 != 0) {
      return false;
    }
  }

  return true;
}

auto PerformThinningStep(const cv::Mat& processing_mat, cv::Mat& marker, int step) -> void {
  marker.setTo(0);

  for (int i = 1; i < processing_mat.rows - 1; ++i) {
    for (int j = 1; j < processing_mat.cols - 1; ++j) {
      if (processing_mat.at<uchar>(i, j) == kBackgroundValue) {
        continue;
      }

      std::array<uchar, kNeighborsPixelsSize> p{};
      GetNeighborsPixels(processing_mat, i, j, p);

      if (ShouldMarkPixel(p, step)) {
        marker.at<uchar>(i, j) = kThinningValue;
      }
    }
  }
}

auto ZhangSuenThinning(const cv::Mat& input_binary_image) -> cv::Mat {
  if (input_binary_image.type() != CV_8UC1) {
    std::cerr << "[ERROR] CV_8UC1 형식의 바이너리 이미지 필요" << "\n";
    return cv::Mat{};
  }
  const int kPixelIndexSix = 6;

  cv::Mat processing_mat;
  input_binary_image.convertTo(processing_mat, CV_8U, 1.0 / kMaxPixelColor);
  cv::Mat marker = cv::Mat::zeros(processing_mat.size(), CV_8UC1);

  bool is_running = true;

  while (is_running) {
    is_running = false;

    // Step 1
    PerformThinningStep(processing_mat, marker, 0);
    if (cv::countNonZero(marker) > 0) {
      processing_mat -= marker;
      is_running = true;
    }

    // Step 2
    PerformThinningStep(processing_mat, marker, 1);
    if (cv::countNonZero(marker) > 0) {
      processing_mat -= marker;
      is_running = true;
    }
  }

  return processing_mat * kMaxPixelColor;
}
