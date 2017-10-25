/*
 * queue.h
 *
 *  Created on: Oct 17, 2017
 *      Author: heli
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include"datos.h"
#define NULL_ENTRY -1

#define QUEUE_CAPACITY 20

typedef struct {
	int front, rear, size;
	unsigned capacity;
	int array[QUEUE_CAPACITY];
} queue;

extern void init_queue(queue *q);
extern void enqueue(int n, queue *q);
extern int dequeue(queue *q);

extern bool is_empty(queue *q);
extern bool is_full(queue *q);
extern int front(queue* queue);
extern int rear(queue* queue);

#endif /* QUEUE_H_ */
