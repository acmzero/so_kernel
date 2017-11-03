/*
 * mancolas.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancolas.h"
#include"libs.h"
#include<GRAPHICS.H>
#include<STDLIB.H>
#ifndef NULL
#include<_NULL.H>
#endif

queue listos[MAX_PRIORITY];

int tiempo_retrasa = -1;
RetrasaListNode retrasa_head;

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

char str_to_log[50];
void log_lista_retrasa() {
	RetrasaListNode e;
	e = retrasa_head;
	log_line("->start\n");
	while (e != NULL) {
		sprintf(str_to_log, "->%s / %d\n", pcbs[e->id].name, e->time);
		log_line(str_to_log);
		e = e->next;
	}
	log_line("->NULL\n");
	log_line("->end\n");
}

void saca_retrasa() {
	RetrasaListNode h = retrasa_head;
	log_line("saca_retrasa\n");
	if (h != NULL) {
		retrasa_head = h->next;
		actualizaTiempoRetrasa();
		inserta(h->id);
		free(h);
		log_lista_retrasa();
		if (retrasa_head != NULL && retrasa_head->time == 0) {
			saca_retrasa();
		}
	}
}

void actualizaTiempoRetrasa() {
	if (retrasa_head != NULL) {
		tiempo_retrasa = retrasa_head->time;
	}
}

void mete_cola_retrasa(int time) {
	int sum_time;
	RetrasaListNode e, prev;

	e = retrasa_head;
	prev = NULL;
	sum_time = 0;
	while (e != NULL) {
		sum_time += e->time;
		if (sum_time == time) {
			log_line("Inserting right time = 0\n");
			insertRight(e, running_pcb, 0);
			log_lista_retrasa();
			return;
		}
		if (time < sum_time) {
			if (prev == NULL) {
				log_line("Inserting head prev==NULL \n");
				retrasa_head = createNode(running_pcb, time);
				retrasa_head->next = e;
				e->time = e->time - time;
				actualizaTiempoRetrasa();
				log_lista_retrasa();
			} else {
				log_line("Inserting right time < sum_time \n");
				insertRight(prev, running_pcb, time - prev->time);
				log_lista_retrasa();
			}
			return;
		}

		prev = e;
		e = e->next;
	}
	if (prev == NULL) {
		log_line("Inserting head \n");
		retrasa_head = createNode(running_pcb, time);
		actualizaTiempoRetrasa();
		log_lista_retrasa();
	} else {
		log_line("Inserting right time - sum_time \n");
		insertRight(prev, running_pcb, time - sum_time);
		log_lista_retrasa();
	}

}
void insertRight(RetrasaListNode prev, int p, int t) {
	RetrasaListNode n = prev->next;
	prev->next = createNode(p, t);
	prev->next->next = n;
	if (n != NULL) {
		n->time = n->time - t;
	}
}

RetrasaListNode createNode(int id, int t) {
	RetrasaListNode n;
	n = malloc(sizeof(struct RetrasaNode));
	n->id = id;
	n->time = t;
	n->next = NULL;
	return n;
}

