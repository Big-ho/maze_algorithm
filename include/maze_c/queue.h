#pragma once

#include "maze_c/core.h"
#define QUEUE_SIZE 1000

typedef struct {
  point_t data[QUEUE_SIZE];
  int front;
  int rear;
} queue_t;

void init_queue(queue_t *q);
int is_empty(queue_t *q);
int is_full(queue_t *q);
void enqueue(queue_t *q, point_t item);
point_t dequeue(queue_t *q);