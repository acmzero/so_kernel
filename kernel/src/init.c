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
	activa(&proceso_1, "p1");
	activa(&proceso_6, "p6");
	timer_handler_old = getvect(TIMER_INT);

	setvect(TIMER_INT, timer_handler_new);

	while (true) {
		if (esc_pressed) {
			setvect(TIMER_INT, timer_handler_old);
			exit(0);
		}
	}

	return 0;
}

