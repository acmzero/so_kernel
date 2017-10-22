/*
 * mancolas.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancolas.h"
#include"libs.h"
#include<GRAPHICS.H>

queue listos[MAX_PRIORITY];
l_list lista_retrasa;

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
int mete_y = 70;
void mete_cola_retrasa(int time) {
	int time_count, t;
	list_node *e, *n;
	if (!cola_retrasa_initialized) {
		init_list(&lista_retrasa);
		cola_retrasa_initialized = true;
	}
	if (lista_retrasa.size == 0) {
		insert_head(running_pcb, time, &lista_retrasa);
		print_line(2, 10, mete_y, "insert head", WHITE);
		mete_y = mete_y + 10;
	} else {
		e = lista_retrasa.head;
		n = new_list_node(running_pcb, 0);
		time_count = 0;
		while (e > 0) {
			time_count = e->value + time_count;
			if (time == time_count) {
				//inserta a la derecha
				print_line(2, 10, mete_y, "insert right", WHITE);
				mete_y += 10;
				n->value = 0;
				n->next = e->next;
				n->prev = e;
				n->next->prev = n;
				e->next = n;
				lista_retrasa.size++;
				return;
			} else if (time < time_count) {
				//inserta a la izquierda
				print_line(2, 10, mete_y, "insert left", WHITE);
				mete_y += 10;
				n->value = time + e->value - time_count;
				n->next = e;
				n->prev = e->prev;
				e->prev = n;
				n->prev->next = n;
				n->next->value = n->next->value - n->value;
				lista_retrasa.size++;
				return;
			}
			e = e->next;
		}
		//si no se inserto en el while, ponerlo en tail - count_timer
		free(n);
		insert_tail(running_pcb, time - time_count, &lista_retrasa);
	}

}
