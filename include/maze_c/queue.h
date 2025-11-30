#pragma once

#include "maze_c/types.h"

#define QUEUE_SIZE 1000

typedef struct {
  Point data[QUEUE_SIZE];
  int front;
  int rear;
} Queue;

void init_queue(Queue *q);
int is_empty(Queue *q);
int is_full(Queue *q);
void enqueue(Queue *q, Point item);
Point dequeue(Queue *q);