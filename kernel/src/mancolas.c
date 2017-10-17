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
queue colas[COLAS_SIZE];

bool is_full(int q) {
	return colas[q].size == colas[q].capacity;
}

bool is_empty(int q) {
	return colas[q].size == 0;
}

void inserta(int pcb, int q) {
	if (is_full(q)) {
		return;
	}
	if (q == LISTOS) {
		if (pcbs[pcb].state == TERMINATED) {
			return;
		}
		pcbs[pcb].state = READY;
	}

	colas[q].rear = (colas[q].rear + 1) % colas[q].capacity;
	colas[q].array[colas[q].rear] = pcb;
	colas[q].size = colas[q].size + 1;
}

char str[20];
char str1[20];
int obtener_primero(int q) {
	int x;
	if (is_empty(q)) {
		return NULL_ENTRY;
	}
	x = colas[q].array[colas[q].front];
	colas[q].front = (colas[q].front + 1) % colas[q].capacity;
	colas[q].size = colas[q].size - 1;
	if (x == NULL_ENTRY || (q == LISTOS && pcbs[x].state == TERMINATED)) {
		return obtener_primero(q);
	}
	return x;
}
void sacar(int n, int q) {
	int i;
	for (i = 0; i < colas[q].capacity; i++) {
		if (colas[q].array[i] == n) {
			colas[q].array[i] = NULL_ENTRY;
			return;
		}
	}
}
