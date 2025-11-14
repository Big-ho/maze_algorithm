#pragma once

// row, col 좌표
typedef struct {
  int x;
  int y;
} point_t;

// 문의 넓이 관련
// TODO: 해당 타입은 이제 필요 없어졌음, 맵 축소가 가능해짐
typedef struct {
  point_t start;
  point_t end;
  int width;
} portal_info_t;

// 출입구 정보
typedef struct {
  portal_info_t entry_info;
  portal_info_t exit_info;
} portal_pair_t;

void display_2d_map(int **map, int hight, int width, point_t *human);
int run_2d_custom_game();
int run_2d_random_game();

// 3d map
int run_3d_custom_game();
int run_3d_random_game();