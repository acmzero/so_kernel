/*
 * mancolas.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"mancolas.h"
#include"datos.h"

cola *listos;
void inserta(PCB *p, cola *q) {
	cola_entry *e = malloc(sizeof(cola_entry));
	cola_entry *n;
	e->value = p;
	e->next = NULL;
	if (q->head == NULL) {
		printf("inserting head %s %d\n", p->name, p->id);
		q->head = e;
	} else {
		printf("inserting tail %s %d\n", p->name, p->id);
		n = q->head;
		while(n->next != NULL){
			n = n->next;
		}
		n->next = e;
	}
}

cola_entry *obtener_primero(cola *q) {
	printf("primero %s %d\n", q->head->value->name, q->head->value->id);
	return q->head;
}

void saca(PCB *p, cola *q) {
	cola_entry *e, *prev;
	e = q->head;
	prev=NULL;
	while (e != NULL) {
		if (e->value == p) {
			if (prev != NULL){
				prev->next = e->next;
			}
			return;
		}
		prev = e;
		e = e->next;
	}
}
