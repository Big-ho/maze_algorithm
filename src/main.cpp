#include <iostream>
#include <opencv2/opencv.hpp>
#include <ostream>

#include "maze_cpp/algorithm.hpp"
// #include "maze_cpp/utils.hpp"

auto main() -> int {
  try {
    std::string image_path("image/maze1.png");

    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);

    if (image.empty()) {
      std::cerr << "[ERROR] 이미지를 로드할 수 업습니다" << image_path << "\n";
      return 1;
    }

    const int kMagicMaxVal = 255;

    std::cout << "이미지 로드 성공!" << "\n";
    std::cout << "크기: " << image.cols << "x" << image.rows << "\n";
    std::cout << "채널: " << image.channels() << "\n";

    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    cv::Mat binary_image;
    cv::threshold(gray_image, binary_image, 0, kMagicMaxVal, cv::THRESH_BINARY | cv::THRESH_OTSU);

    cv::Mat morphologid_image;
    cv::Mat kernel;
    cv::Mat inverted_binary_image = kMagicMaxVal - binary_image;

    kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size_<int>(3, 3));
    cv::morphologyEx(inverted_binary_image, morphologid_image, cv::MORPH_DILATE, kernel);

    /* txt로 확인용 */
    // InputBinaryDataToTextFile(morphologid_image);

    cv::Mat thinned_image = ZhangSuenThinning(morphologid_image);

    cv::imshow("original", image);
    cv::imshow("gray", gray_image);
    cv::imshow("binary", binary_image);
    cv::imshow("dilated", morphologid_image);
    cv::imshow("thinned", thinned_image);

    cv::waitKey(0);

    return 0;
  } catch (const std::exception& e) {
    std::cerr << "[ERROR] 오류 발생" << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "[ERROR] 알 수 없는 오류 발생" << "\n";
    return 1;
  }
}
