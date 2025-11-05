#include <fstream>
#include <iostream>

#include "maze_cpp/utils.hpp"

auto InputBinaryDataToTextFile(const cv::Mat& mat_data) -> void {
  if (mat_data.empty()) {
    std::cerr << "[ERROR] Mat이 비어있습니다." << "\n";
    return;
  }

  std::ofstream fout;
  fout.open("maze_data.txt", std::ios::out | std::ios::trunc);

  if (!fout.is_open()) {
    std::cerr << "[ERROR] maze_data 파일 오픈 실패했습니다." << "\n";
    return;
  }

  const int kRowSize = mat_data.rows;
  const int kColSize = mat_data.cols;

  fout << "Rows: " << kRowSize << ", Cols: " << kColSize << "\n";

  for (int i = 0; i < kRowSize; ++i) {
    for (int j = 0; j < kColSize; ++j) {
      uchar pixel_value = mat_data.at<uchar>(i, j);
      fout << static_cast<int>(pixel_value) << " ";
    }
    fout << "\n";
  }

  fout.close();
  std::cout << "데이터가 성공적으로 써졌습니다." << "\n";
}