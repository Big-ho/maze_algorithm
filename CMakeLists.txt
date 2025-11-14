cmake_minimum_required(VERSION 3.10)
project(maze_c C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_CLANG_TIDY clang-tidy)

add_library(${PROJECT_NAME}_lib STATIC)
target_sources(${PROJECT_NAME}_lib
  PRIVATE
    # utils
    src/utils/display_2d_array.c
    src/utils/load_file.c
    src/utils/memory.c
    src/utils/terminal.c
    # core
    src/core/2d_map.c
    src/core/3d_map.c
    src/core/game.c
    src/core/zhang_suen_thinning.c
    src/core/pooling.c

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