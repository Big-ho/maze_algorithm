#include "maze_c/game.h"
#include "maze_c/game_runner.h"
#include "maze_c/search.h"
#include "maze_c/types.h"
#include "maze_c/utils.h"

#include <stdio.h>

int run_custom_game(Map *map) {
  init_term();

  int global_tick = 0;
  int tracker_tick = 0;

  const int ENDING_DELAY = 2000;
  const int FPS_DELAY = 30;
  const int WAIT_TIME = 3;
  const int TRACKER_DELAY_TICK = WAIT_TIME * (1000 / FPS_DELAY);
  const int TRACKER_BASE_SPEED = 15;

  while (1) {
    render();
    if (global_tick < TRACKER_DELAY_TICK) {
      printf("\n\033[31m 추격: %d\033[0m\n\n",
             TRACKER_DELAY_TICK - global_tick);
    }
    display_map(*map);

    if (kbhit()) {
      int key = getchar();
      if (process_input(map, key)) { // q 입력
        break;
      }
    }

    if (global_tick >= TRACKER_DELAY_TICK) {
      int tracker_speed = get_dynamic_tracker_delay(map->player, map->tracker,
                                                    TRACKER_BASE_SPEED);
      tracker_tick++;
      if (tracker_tick >= tracker_speed) {
        tracker_tick = 0;
        map->tracker = get_next_step(map);
      }

      if (is_gameover(*map)) {
        render();
        display_map(*map);
        printf("[GAME OVER]\n");
        sleep_ms(ENDING_DELAY);
        break;
      }
    }

    if (is_clear(*map)) {
      render();
      display_map(*map);
      printf("[GAME CLEAR]\n");
      sleep_ms(ENDING_DELAY);
      break;
    }

    global_tick++;
    sleep_ms(FPS_DELAY);
  }
  reset_term();

  return 0;
}