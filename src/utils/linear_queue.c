#include "maze_c/queue.h"

#include <stdio.h>

void init_queue(Queue *q) {
  q->front = -1;
  q->rear = -1;
}

int is_empty(Queue *q) { return q->front == q->rear; }

int is_full(Queue *q) { return q->rear - 1 == QUEUE_SIZE; }

void enqueue(Queue *q, Point item) {
  if (is_full(q)) {
    fprintf(stderr, "[ERROR] Queue가 꽉 찼습니다.\n");
    return;
  }
  q->data[++(q->rear)] = item;
}

Point dequeue(Queue *q) {
  if (is_empty(q)) {
    fprintf(stderr, "[ERROR] Queue가 비었습니다.\n");
    Point err = {-1, -1};
    return err;
  }
  return q->data[++(q->front)];
}