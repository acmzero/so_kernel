/*
 * mancolas.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"datos.h"

#ifndef MANCOLAS_H_
#define MANCOLAS_H_
#define NULL_ENTRY -1
#define QUEUE_CAPACITY 20
#define COLAS_SIZE 5

typedef enum {
	LISTOS, TECLADO
} colas_idx;

typedef struct {
	int front, rear, size;
	unsigned capacity;
	int array[QUEUE_CAPACITY];
} queue;

extern void inserta(int pcb, int q);
extern void sacar(int n, int q);
extern int obtener_primero(int q);

extern bool is_empty(int q);

extern queue colas[];

#endif /* MANCOLAS_H_ */
