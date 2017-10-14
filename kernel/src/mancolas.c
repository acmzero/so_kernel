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

#define MAX 10

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

bool isFull() {
	return itemCount == MAX;
}
void inserta(int pcb) {
	if (!isFull()) {
		if (rear == MAX - 1) {
			rear = -1;
		}
		intArray[++rear] = pcb;
		itemCount++;
	}
}
void sacar(int n) {
	pcbs[n].state = TERMINATED;
}

int obtener_primero() {
	int data = intArray[front++];
	if (front == MAX) {
		front = 0;
	}
	itemCount--;
	if (pcbs[data].state == TERMINATED) {
		return obtener_primero();
	}
	return data;
}
