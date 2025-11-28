#include "maze_c/core.h"
#include "maze_c/image_reader.h"
#include "maze_c/pooling.h"
#include "maze_c/thinning.h"
#include "maze_c/thresholding.h"
#include "maze_c/utils.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// 게임용 뷰어
void display_2d_map(int **map, int height, int width, point_t *human) {
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      if (human && row == human->y && col == human->x) {
        // printf("\033[31m■\033[0m");
        printf("@");
      } else if (map[row][col] == 1) {
        // printf("■");
        printf("#");
      } else {
        // printf("\033[30m■\033[0m");
        printf(" ");
      }
    }
    putchar('\n');
  }
}

static void render() { printf("\033[H\033[J"); }

// 문 찾아 portal_info_t 구조체에 저장
static int find_portal(const int *row, int row_index, int width,
                       portal_info_t *out_portal) {
  int start_col = -1;
  int count_col = 0;

  for (int col = 0; col < width; col++) {
    if (row[col] == 0) { // 문
      if (start_col == -1) {
        start_col = col;
      }
      count_col++;
    } else {                 // 벽
      if (start_col != -1) { // 한번이라도 문에 만났을 때
        out_portal->start.x = start_col;
        out_portal->start.y = row_index;
        out_portal->end.x = col - 1;
        out_portal->end.y = row_index;
        out_portal->width = count_col;
        return 0;
      }
    }
  }
  if (start_col != -1) { // 0이 끝까지 이어질 경우
    out_portal->start.x = start_col;
    out_portal->start.y = row_index;
    out_portal->end.x = count_col - 1;
    out_portal->end.y = row_index;
    out_portal->width = count_col;
    return 0;
  }
  return 1; // 0이 없을 경우
}

// 입출구 찾기
static int find_entry_exit(int **map, int height, int width,
                           portal_pair_t *out_portal_pair) {
  int is_entry_found = 0;
  int is_exit_found = 0;

  is_exit_found = find_portal(map[0], 0, width, &out_portal_pair->exit_info);
  is_entry_found = find_portal(map[height - 1], height - 1, width,
                               &out_portal_pair->entry_info);

  return is_exit_found && is_entry_found;
}

static int process_input(int **map, int key, point_t *out_p) {
  if (key == 113 || key == 81) { // q
    return 1;                    // 종료
  }
  int new_x = out_p->x;
  int new_y = out_p->y;

  // wasd
  if (key == 119 || key == 87) {
    new_y -= 1; // 위
  } else if (key == 97 || key == 65) {
    new_x -= 1; // 왼
  } else if (key == 115 || key == 83) {
    new_y += 1; // 아
  } else if (key == 100 || key == 68) {
    new_x += 1; // 오
  }

  if (map[new_y][new_x] != 1) {
    out_p->x = new_x;
    out_p->y = new_y;
  }

  return 0;
}

// 2d 커스텀 게임
int run_2d_custom_game() {
  const char *test_map_path = "image/maze10by10.bmp";
  int height = 0;
  int width = 0;

  // bmp 이미지 파일 읽고 바이너리 배열로 변경
  rgb_quad_t **bmp_2d_arr = load_bmp(test_map_path, &height, &width);
  int **binary_2d_arr = create_2d_array(height, width);
  otsu_thresholding(bmp_2d_arr, binary_2d_arr, height, width);
  free_bmp(bmp_2d_arr);

  // 세선화 알고리즘 적용
  zhang_suen_thinning(binary_2d_arr, height, width);

  // 맵 축소 적용
  int reduced_map_size = estimate_reduce_map_size(height);
  int **reduced_map = create_2d_array(reduced_map_size, reduced_map_size);
  apply_reduce_map(binary_2d_arr, reduced_map, height, width, reduced_map_size);
  free_2d_array(binary_2d_arr);

  // 축소 후 새로운 높이, 너비
  height = reduced_map_size;
  width = reduced_map_size;

  if (reduced_map == NULL) {
    fprintf(stderr, "[ERROR] 맵 읽기 실패⚠️");
    return -1;
  }

  portal_pair_t entry_exit_info = {0};
  if (find_entry_exit(reduced_map, height, width, &entry_exit_info) != 0) {
    return -1; // 입출구 찾기 실패
  };

  int entry_center =
      (entry_exit_info.entry_info.start.x + entry_exit_info.entry_info.end.x) /
      2;

  point_t human = {entry_center, height - 1}; // (x,y)

  int is_running = 1;
  init_term();
  while (is_running) {
    render();
    int original_value = reduced_map[human.y][human.x];
    display_2d_map(reduced_map, height, width, &human);
    reduced_map[human.y][human.x] = original_value;

    if (kbhit()) {
      int key = getchar();
      if (process_input(reduced_map, key, &human)) {
        is_running = 0;
      }
    }

    if (human.y == entry_exit_info.exit_info.end.y &&
        human.x == entry_exit_info.exit_info.end.x) {
      is_running = 0;
      render();
      display_2d_map(reduced_map, height, width, &human);
      printf("\n 축하합니다~ \n");
      sleep_ms(2000);
    }

    sleep_ms(30);
  }

  reset_term();
  free_2d_array(reduced_map);

  return 0;
}

// TODO: 미완성
int run_2d_random_game() { return 0; }