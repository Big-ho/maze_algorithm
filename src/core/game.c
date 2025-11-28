#include "maze_c/game.h"

#include "maze_c/core.h"
#include <stddef.h>
#include <stdio.h>

static const char *map_type_list[MAP_COUNT + 1] = {"Custom", "Random", "EXIT"};

// 게임 실행하는 함수 포인터 타입
typedef int (*game_runner_func_t)(void);

// 입력 버퍼 지우는 유틸
static void buffer_clear() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// 선택한 맵 타입 유효성 확인
static int is_valid_map(int index) { return (index >= 0 && index < MAP_COUNT); }

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

// 맵 타입 선택 관리 & 선택 주소 반환
static int select_map_return_index() {
  printf("\n[%s]\n", "Select Map Type");

  for (int i = 0; i < MAP_COUNT; i++) {
    printf("%d. %s\n", i + 1, map_type_list[i]);
  }
  printf("%d. EXIT\n", MAP_COUNT + 1);

  int choice = select_choice(MAP_COUNT + 1);
  if (choice == -1) {
    return MAP_EXIT;
  }
  if (choice == MAP_COUNT + 1) {
    return MAP_EXIT;
  }

  return choice - 1;
}

// 각 게임 실행 함수를 위한 2D 디스패치 테이블
static game_runner_func_t game_dispatch_table[MAP_COUNT] = {run_2d_custom_game,
                                                            run_2d_random_game};

// 게임 실행을 위한 메인 루프 함수
int game_loop() {
  while (1) {
    int selectd_map_index = select_map_return_index();
    if (selectd_map_index == MAP_EXIT) {
      break;
    }
    if (!is_valid_map(selectd_map_index)) {
      break;
    }

    game_dispatch_table[selectd_map_index]();
  }

  return 0;
}
