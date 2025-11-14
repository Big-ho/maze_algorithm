#include "maze_c/game.h"

#include "maze_c/core.h"
#include <stddef.h>
#include <stdio.h>

// 게임 실행하는 함수 포인터 타입
typedef int (*game_runner_func_t)(void);

// 차원 선택 관리 배열
static const char *dimension_list[DIMENSION_FUNCS_SIZE + 1] = {"2D", "3D",
                                                               "EXIT"};
// 맵 타입 선택 관리 배열
static const char *map_type_list[MAP_FUNCS_SIZE + 1] = {"Custom", "Random",
                                                        "EXIT"};

// 입력 버퍼 지우는 유틸
static void buffer_clear() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// 선택한 차원 유효성 확인
static int is_valid_dimension(int index) {
  return (index >= 0 && index < DIMENSION_FUNCS_SIZE);
}

// 선택한 맵 타입 유효성 확인
static int is_valid_map(int index) {
  return (index >= 0 && index < MAP_FUNCS_SIZE);
}

// 선택 관리 유틸
static int select_choice(int max) {
  int selected = 0;

  if (scanf("%d", &selected) != 1) {
    fprintf(stderr, "[ERROR] 숫자를 입력해주세요\n");
    buffer_clear();
    return -1;
  }

  if (selected < 1 || selected > max) {
    fprintf(stderr, "[ERROR] 1~%d 정해진 범위 내 번호를 선택해주세요.\n", max);
    buffer_clear();
    return -1;
  }

  return selected;
}

// 차원 선택 관리 & 선택 주소 반환
static int select_dimension_return_index() {
  printf("\n[MAZE] Select Dimension\n");

  for (int i = 0; i < DIMENSION_FUNCS_SIZE; i++) {
    printf("%d. %s\n", i + 1, dimension_list[i]);
  }
  printf("%d. EXIT\n", DIMENSION_FUNCS_SIZE + 1);

  int choice = select_choice(DIMENSION_FUNCS_SIZE + 1);
  if (choice == -1) {
    return DIMENSION_EXIT;
  }
  if (choice == DIMENSION_FUNCS_SIZE + 1) {
    return DIMENSION_EXIT;
  }

  return choice - 1;
}

// 맵 타입 선택 관리 & 선택 주소 반환
static int select_map_return_index(int dimension_index) {
  if (!is_valid_dimension(dimension_index)) {
    return MAP_EXIT;
  }

  printf("\n[%s]\n", dimension_list[dimension_index]);

  for (int i = 0; i < MAP_FUNCS_SIZE; i++) {
    printf("%d. %s\n", i + 1, map_type_list[i]);
  }
  printf("%d. EXIT\n", MAP_FUNCS_SIZE + 1);

  int choice = select_choice(MAP_FUNCS_SIZE + 1);
  if (choice == -1) {
    return MAP_EXIT;
  }
  if (choice == MAP_FUNCS_SIZE + 1) {
    return MAP_EXIT;
  }

  return choice - 1;
}

// 각 게임 실행 함수를 위한 2D 디스패치 테이블
static game_runner_func_t
    game_dispatch_table[DIMENSION_FUNCS_SIZE][MAP_FUNCS_SIZE] = {
        {run_2d_custom_game, run_2d_random_game},
        {
            run_3d_custom_game,
            run_3d_random_game,
        }};

// 게임 실행을 위한 메인 루프 함수
int game_loop() {
  int is_running = 1;

  while (is_running) {
    int selectd_dimension_index = select_dimension_return_index();
    if (selectd_dimension_index == DIMENSION_EXIT) {
      is_running = 0;
      continue;
    }
    if (!is_valid_dimension(selectd_dimension_index)) {
      is_running = 0;
      continue;
    }

    while (1) {
      int selectd_map_index = select_map_return_index(selectd_dimension_index);
      if (selectd_map_index == MAP_EXIT) {
        break;
      }
      if (!is_valid_map(selectd_map_index)) {
        is_running = 0;
        break;
      }

      /*
      NOTE: 정적 분석기 문제, 유효성 검사를 완벽하게 했지만 인식하지 못함
      */
      // NOLINTNEXTLINE(clang-analyzer-security.ArrayBound)
      game_dispatch_table[selectd_dimension_index][selectd_map_index]();
      is_running = 0;
      break;
    }
  }
  return 0;
}
