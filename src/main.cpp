#include <iostream>
#include <opencv2/opencv.hpp>

auto main() -> int {
  try {
    std::string image_path("image/maze1.png");

    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);

    if (image.empty()) {
      std::cerr << "[ERROR] 이미지를 로드할 수 업습니다" << image_path << '\n';
      return 1;
    }

    std::cout << "이미지 로드 성공!" << '\n';
    std::cout << "크기: " << image.cols << "x" << image.rows << '\n';
    std::cout << "채널: " << image.channels() << '\n';

    cv::imshow("로드된 이미지", image);

    cv::waitKey(0);

    return 0;
  } catch (const std::exception& e) {
    std::cerr << "[ERROR] 오류 발생" << e.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "[ERROR] 알 수 없는 오류 발생" << '\n';
    return 1;
  }
}
