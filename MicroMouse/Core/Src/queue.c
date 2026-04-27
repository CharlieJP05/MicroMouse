#include "Queue.h"

// init
void Queue_init(Queue *q) {
	q->front = 0;
	q->rear = -1;
	q->count = 0;
}

// checks
int isEmpty(Queue *q) {
	return q->count == 0;
}

int isFull(Queue *q) {
	return q->count == QUEUE_SIZE;
}

// append (enqueue)
void append(Queue *q, int x, int y) {
	if (isFull(q)) {
		return;
	}

	q->rear = (q->rear + 1) % QUEUE_SIZE;

	q->arr[q->rear].x = x;
	q->arr[q->rear].y = y;

	q->count++;
}

// pop (dequeue)
Position pop(Queue *q) {
	Position empty = {0, 0};

	if (isEmpty(q)) {
		return empty;
	}

	Position item = q->arr[q->front];

	q->front = (q->front + 1) % QUEUE_SIZE;
	q->count--;

	return item;
}
