#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <opencv2/opencv.hpp>

auto ZhangSuenThinning(const cv::Mat& input_binary_image) -> cv::Mat;

#endif  // ALGORITHM_HPP