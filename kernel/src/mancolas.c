/*
 * mancolas.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancolas.h"
#include"datos.h"
#include"libs.h"
#include<GRAPHICS.H>

queue listos;

void inserta(int n, queue *q) {
	if (pcbs[n].state == TERMINATED) {
		return;
	}
	pcbs[n].state = READY;
	enqueue(n, q);
}

int obtener_primero(queue *q) {
	int x;
	x = dequeue(q);
	if (x == NULL_ENTRY || pcbs[x].state == TERMINATED) {
		return obtener_primero(q);
	}
	return x;
}
void sacar(int n, queue *q) {
	int i;
	for (i = 0; i < q->capacity; i++) {
		if (q->array[i] == n) {
			q->array[i] = NULL_ENTRY;
			return;
		}
	}
}

void inicializa_colas() {
	init_queue(&listos);
}
