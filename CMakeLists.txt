cmake_minimum_required(VERSION 3.10)
project(maze_c C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_CLANG_TIDY clang-tidy)

add_library(${PROJECT_NAME}_lib STATIC)
target_sources(${PROJECT_NAME}_lib
  PRIVATE
    src/utils/load_file.c
    src/core/2d_map.c
)

target_include_directories(${PROJECT_NAME}_lib
  PUBLIC
    include
  PRIVATE
    src
)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_NAME}_lib
)