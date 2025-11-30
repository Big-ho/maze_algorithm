#include "maze_c/game_runner.h"

#include "maze_c/game.h"
#include "maze_c/utils.h"

#include <stdio.h>

int run_custom_game(Map *map) {
  init_term();
  while (1) {
    render();
    display_map(*map);

    if (kbhit()) {
      int key = getchar();
      if (process_input(map, key)) { // q 입력
        break;
      }
    }

    if (is_clear(*map)) {
      render();
      printf("[GAME CLEAR]\n");
      sleep_ms(1000);
      break;
    }

    sleep_ms(30);
  }
  reset_term();

  return 0;
}