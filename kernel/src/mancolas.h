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

typedef struct {
	int front, rear, size;
	unsigned capacity;
	int array[QUEUE_CAPACITY];
} queue;

extern void inserta(int pcb);
extern void sacar(int n);
extern int obtener_primero();

extern queue listos;

#endif /* MANCOLAS_H_ */
