#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

#define QUEUE_SIZE 64

typedef struct {
	int x;
	int y;
} Position;

typedef struct {
	int front;
	int rear;
	int count;
	Position arr[QUEUE_SIZE];
} Queue;

// init
void Queue_init(Queue *q);

// state
int isEmpty(Queue *q);
int isFull(Queue *q);

// operations
void append(Queue *q, int x, int y);
Position pop(Queue *q);
Position peek(Queue *q);
#endif
