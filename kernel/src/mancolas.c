/*
 * mancolas.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancolas.h"
#include"libs.h"
#include<GRAPHICS.H>
#include<ALLOC.H>

queue listos[MAX_PRIORITY];
l_list *lista_retrasa;

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

bool cola_retrasa_initialized = false;
void mete_cola_retrasa(int time) {
	int time_count, t;
	list_node *e, *n, *prev;
	if (!cola_retrasa_initialized) {
		lista_retrasa = (l_list*) malloc(sizeof(l_list));
		lista_retrasa->head = NULL;
		cola_retrasa_initialized = true;
	}
	if (lista_retrasa->head == NULL) {
		add_first(running_pcb, time, lista_retrasa);
		return;
	} else {
		e = lista_retrasa->head;
		time_count = 0;
		while (e != NULL) {
			time_count = e->value + time_count;
			if (time == time_count) {
				//inserta a la derecha
				n = malloc(sizeof(list_node));
				n->id = running_pcb;
				n->value = 0;
				n->next = e->next;
				e->next = n;
				return;
			} else if (time < time_count) {
				//inserta a la izquierda
				if (e == lista_retrasa->head) {
					add_first(running_pcb, (time + (e->value) - time_count),
							lista_retrasa);
				} else {
					n = malloc(sizeof(list_node));
					n->id = running_pcb;
					n->value = (time + (e->value) - time_count);
					n->next = e;
					e->value = e->value - n->value;
					prev->next = n;
				}
				return;
			}
			prev = e;
			e = e->next;
		}
		add_last(running_pcb, time - time_count, lista_retrasa);
	}

}
