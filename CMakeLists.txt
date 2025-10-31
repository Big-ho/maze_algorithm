cmake_minimum_required(VERSION 3.16)
project(maze_cpp LANGUAGES CXX)

# C++ 설정 및 컴파일러 플래그
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

# 라이브러리 (OpenCV) 설정
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  message(STATUS "OpenCV: Found OpenCV ${OpenCV_VERSION}")
  set(OPENCV_REQUIRED_LIBS ${OpenCV_LIBS})
  set(OPENCV_REQUIRED_INCLUDES ${OpenCV_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "OpenCV not found!")
endif()

# # 공통 라이브러리 타겟 (std_cpp_lib)
# add_library(${PROJECT_NAME}_lib STATIC)
# target_sources(${PROJECT_NAME}_lib
#   PRIVATE
# )

# # 라이브러리 인클루드 경로 설정
# target_include_directories(${PROJECT_NAME}_lib
#   PUBLIC
#     include
#     ${OPENCV_REQUIRED_INCLUDES}
#   PRIVATE
#     src
# )

# 메인 실행 파일
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    # ${PROJECT_NAME}_lib
    ${OPENCV_REQUIRED_LIBS}
)