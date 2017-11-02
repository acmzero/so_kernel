/*
 * mancolas.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancolas.h"
#include"libs.h"
#include<GRAPHICS.H>

queue listos[MAX_PRIORITY];

void inserta(int n) {
	pcbs[n].state = READY;
	enqueue(n, &listos[pcbs[n].priority]);
}

int obtener_primero() {
	int i;
	for (i = 0; i < MAX_PRIORITY; i++) {
		if (!is_empty(&listos[i])) {
			return front(&listos[i]);
		}
	}
	return NULL_ENTRY;
}
void sacar(int n) {
	int i, x, j, s;
	for (i = 0; i < MAX_PRIORITY; i++) {
		s = listos[i].size;
		for (j = 0; j < s; j++) {
			x = dequeue(&listos[i]);
			if (x != n) {
				enqueue(x, &listos[i]);
			}
		}
	}
}

void inicializa_colas() {
	int i;
	for (i = 0; i < MAX_PRIORITY; i++) {
		init_queue(&listos[i]);
	}
}

