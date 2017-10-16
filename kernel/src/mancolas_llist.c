/*
 * mancolas.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"mancolas.h"
#include"datos.h"
#include<ALLOC.H>

cola listos;
bool cola_initialized = false;
void print_listos() {
	cola_entry *e;
	e = listos.head;
	while (e != NULL_ENTRY) {
		e = e->next;
	}
}
void inserta(int p) {
	cola_entry *e, *n;
	if (p != NULL_ENTRY) {
		e = (cola_entry*) malloc(sizeof(cola_entry));
		e->value = p;
		e->next = NULL_ENTRY;
		if (!cola_initialized) {
			listos.head = e;
			cola_initialized = true;
		} else {
			n = listos.head;
			while (n->next != NULL_ENTRY) {
				n = n->next;
			}
			n->next = e;
		}
	}
}

void saca(int n) {
	cola_entry *e, *f;
	e = listos.head;
	while (e->next != NULL_ENTRY) {
		if (e->next->value == n) {
			f = e->next;
			e->next = f->next;
			e = NULL_ENTRY;
			free(f);
		}
		e = e->next;
	}
	print_listos();
}

int obtener_primero() {
	int x = listos.head->value;
	saca(x);
	return x;
}

