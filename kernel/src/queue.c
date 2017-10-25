/*
 * queue
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"queue.h"

bool is_full(queue *q) {
	return q->size == q->capacity;
}

bool is_empty(queue *q) {
	return q->size == 0;
}

void init_queue(queue *q){
	q->capacity = QUEUE_CAPACITY;
	q->size = 0;
	q->front = 0;
	q->rear = QUEUE_CAPACITY - 1;
}
void enqueue(int n, queue *q) {
	if (is_full(q)) {
		return;
	}
	q->rear = (q->rear + 1) % q->capacity;
	q->array[q->rear] = n;
	q->size = q->size + 1;
}

int dequeue(queue *q) {
	int item;
	if (is_empty(q))
		return NULL_ENTRY;
	item = q->array[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size = q->size - 1;
	return item;
}
int front(queue* q) {
	if (is_empty(q))
		return NULL_ENTRY;
	return q->array[q->front];
}

int rear(queue* q) {
	if (is_empty(q))
		return NULL_ENTRY;
	return q->array[q->rear];
}
