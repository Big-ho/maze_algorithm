#include "maze_c/config.h"
#include "maze_c/game_runner.h"
#include "maze_c/map.h"
#include "maze_c/types.h"
#include "maze_c/utils.h"

#include <stdio.h>

int main() {
  Map game_map;

  const char *menu_list[SELECT_GAME_MENU_COUNT] = {
      "Costom Map",
      "Random Map",
      "Exit",
  };

  while (1) {
    display_menu(menu_list, SELECT_GAME_MENU_COUNT);
    GameType mode = select_menu(SELECT_GAME_MENU_COUNT);
    if (mode == EXIT_GAME) {
      printf("[INFO] === 게임 종료 ===\n");
      break;
    }

    if (mode == CUSTOM_GAME) {
      char filepath[256];
      printf("bmp 이미지 경로를 입력하세요 (예: asset/map.bmp): ");
      if (scanf("%255s", filepath) != 1) {
        fprintf(stderr, "[ERROR] 잘 못된 입력입니다.\n");
        buffer_clear();
        continue;
      }
      buffer_clear();

      if (init_custom_map(&game_map, filepath) < 0) {
        fprintf(stderr, "[ERROR] 경로 확인\n");
        reset_map(&game_map);
        continue;
      }
      run_custom_game(&game_map);
    } else if (mode == RANDOM_GAME) {
      // (랜덤 맵 사이즈 입력)
      // init_random_map(&game_map, size);
      // run_2d_random_game();
    }

    reset_map(&game_map);
  }

  return 0;
}
