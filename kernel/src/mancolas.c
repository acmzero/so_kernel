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

bool is_full() {
	return listos.size == listos.capacity;
}

bool is_empty() {
	return listos.size == 0;
}

void inserta(int pcb) {
	if (is_full()) {
		set_viewport(3);
		outtextxy(10, 10, "listos full no inserting done");
		return;
	}
	if (pcbs[pcb].state == TERMINATED) {
		return;
	}
	pcbs[pcb].state = READY;
	listos.rear = (listos.rear + 1) % listos.capacity;
	listos.array[listos.rear] = pcb;
	listos.size = listos.size + 1;
}

char str[20];
char str1[20];
int obtener_primero() {
	int x;
	if (is_empty()) {
		set_viewport(3);
		outtextxy(10, 20, "listos empty can't get item");
		return NULL_ENTRY;
	}
	x = listos.array[listos.front];
	listos.front = (listos.front + 1) % listos.capacity;
	listos.size = listos.size - 1;
	if (x == NULL_ENTRY || pcbs[x].state == TERMINATED) {
		return obtener_primero();
	}
	if (graphics_itinialized) {
		set_viewport(3);
		setcolor(BLACK);
		outtextxy(10, 30, str);
		outtextxy(10, 50, str1);
		setcolor(WHITE);
		sprintf(str, "first %d", x);
		outtextxy(10, 30, str);
		sprintf(str1, "f %d r %d", listos.front, listos.rear);
		outtextxy(10, 50, str1);
	}
	return x;
}
void sacar(int n) {
	int i;
	for (i = 0; i < listos.capacity; i++) {
		if (listos.array[i] == n) {
			listos.array[i] = NULL_ENTRY;
			return;
		}
	}
}
