#ifndef ZHANG_SUEN_THINNING_HPP
#define ZHANG_SUEN_THINNING_HPP

#include <opencv2/opencv.hpp>

const int kNeighborsPixelsSize = 8;
const int kBackgroundValue = 0;
const int kThinningValue = 1;
const int kMaxPixelColor = 255;
const int kMagicNumberSix = 6;

enum class NeighborsIndexs : uint8_t {
  kP2 = 0,
  kP3 = 1,
  kP4 = 2,
  kP5 = 3,
  kP6 = 4,
  kP7 = 5,
  kP8 = 6,
  kP9 = 7
};

auto ZhangSuenThinning(const cv::Mat& input_binary_image) -> cv::Mat;

#endif  // ZHANG_SUEN_THINNING_HPP