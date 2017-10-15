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
	listos.capacity = QUEUE_CAPACITY;
	listos.size = 0;
	listos.front = 0;
	listos.rear = QUEUE_CAPACITY - 1;
	activa(&proceso_1, "p1");
	activa(&proceso_6, "p6");
	timer_handler_old = getvect(TIMER_INT);

	setvect(TIMER_INT, timer_handler_new);

	while (true) {
		if (esc_pressed) {
			break;
		}
		if (kbhit()) {
			key_c = getch();
			if (key_c == ESC_KEY) {
				esc_pressed = true;
			} else {
				has_key = true;
			}
		}
	}
	setvect(TIMER_INT, timer_handler_old);
	exit(0);

	return 0;
}

