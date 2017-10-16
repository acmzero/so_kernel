/*
 * mancolas.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
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
		/*set_viewport(3);
		 outtextxy(10, 10, "listos full no inserting done");*/
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
		/*set_viewport(3);
		 outtextxy(10, 20, "listos empty can't get item");*/
		return NULL_ENTRY;
	}
	x = colas[q].array[colas[q].front];
	colas[q].front = (colas[q].front + 1) % colas[q].capacity;
	colas[q].size = colas[q].size - 1;
	if (x == NULL_ENTRY || (q == LISTOS && pcbs[x].state == TERMINATED)) {
		return obtener_primero(q);
	}
	/*if (graphics_itinialized) {
	 set_viewport(3);
	 setcolor(BLACK);
	 outtextxy(10, 30, str);
	 outtextxy(10, 50, str1);
	 setcolor(WHITE);
	 sprintf(str, "first %d", x);
	 outtextxy(10, 30, str);
	 sprintf(str1, "f %d r %d", listos.front, listos.rear);
	 outtextxy(10, 50, str1);
	 }*/
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
