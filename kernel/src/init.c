/*
 * init.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"procesos.h"
#include"datos.h"
#include"pripro.h"
#include"mancpu.h"
#include"libs.h"
#include<DOS.H>

#define TIMER_INT 0x8

int main(void) {
	inicializa_colas();
	activa(&proceso_1, "p1");
	activa(&proceso_6, "p6");
	timer_handler_old = getvect(TIMER_INT);

	setvect(TIMER_INT, timer_handler_new);
//	increase_timer_freq();

	while (true) {
		if (esc_pressed) {
			break;
		}
		lee_teclado();
	}
	setvect(TIMER_INT, timer_handler_old);

	return 0;
}

