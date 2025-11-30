#include "maze_c/core.h"
#include "maze_c/queue.h"
#include <stdio.h>

void init_queue(queue_t *q) {
  q->front = -1;
  q->rear = -1;
}

int is_empty(queue_t *q) { return q->front == q->rear; }

int is_full(queue_t *q) { return q->rear - 1 == QUEUE_SIZE; }

void enqueue(queue_t *q, point_t item) {
  if (is_full(q)) {
    fprintf(stderr, "[ERROR] Queue가 꽉 찼습니다.\n");
    return;
  }
  q->data[++(q->rear)] = item;
}

point_t dequeue(queue_t *q) {
  if (is_empty(q)) {
    fprintf(stderr, "[ERROR] Queue가 비었습니다.\n");
    point_t err = {-1, -1};
    return err;
  }
  return q->data[++(q->front)];
}