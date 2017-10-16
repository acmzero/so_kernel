/*
 * init.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"procesos.h"
#include"datos.h"
#include"pripro.h"
#include"mancpu.h"
#include"mancolas.h"
#include<ALLOC.H>
#include<DOS.H>

#define TIMER_INT 0x8

int main(void) {
	int i;
	for (i = 0; i < COLAS_SIZE; i++) {
		colas[i].capacity = QUEUE_CAPACITY;
		colas[i].size = 0;
		colas[i].front = 0;
		colas[i].rear = QUEUE_CAPACITY - 1;
	}
	activa(&proceso_1, "p1");
	activa(&proceso_6, "p6");
	timer_handler_old = getvect(TIMER_INT);

	setvect(TIMER_INT, timer_handler_new);

	while (true) {
		if (esc_pressed) {
			break;
		}
		lee_teclado();
	}
	setvect(TIMER_INT, timer_handler_old);

	return 0;
}

