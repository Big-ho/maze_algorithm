#include "maze_c/search.h"

#include "maze_c/queue.h"
#include "maze_c/types.h"
#include "maze_c/utils.h"

const int DX[4] = {0, 0, -1, 1};
const int DY[4] = {-1, 1, 0, 0};

/* 주의!! return 값 메모리 해제 필수 */
int **bfs(const Map *map) {
  int w = map->width;
  int h = map->height;

  int **dist = create_2d_array(w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      dist[i][j] = -1;
    }
  }

  Queue q;
  init_queue(&q);

  enqueue(&q, map->player);
  dist[map->player.y][map->player.x] = 0;

  while (!is_empty(&q)) {
    Point curr = dequeue(&q);

    if (curr.x == map->tracker.x && curr.y == map->tracker.y) {
      break;
    }

    for (int i = 0; i < 4; i++) {
      int nx = curr.x + DX[i];
      int ny = curr.y + DY[i];

      if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
        if (map->grid[ny][nx] != 1 && dist[ny][nx] == -1) {
          dist[ny][nx] = dist[curr.y][curr.x] + 1;
          enqueue(&q, (Point){nx, ny});
        }
      }
    }
  }
  return dist;
}

Point get_next_step(int **dist, Point *p, int w, int h) {
  int min_dist = 9999;
  Point next_point = *p;
  // 짧은 길 선택
  for (int i = 0; i < 4; i++) {
    int nx = p->x + DX[i];
    int ny = p->y + DY[i];

    if (nx >= 0 && nx < w && ny >= 0 && ny < h && dist[ny][nx] != -1) {
      if (dist[ny][nx] < min_dist) {
        min_dist = dist[ny][nx];
        next_point = (Point){nx, ny};
      };
    }
  }

  return next_point;
}
