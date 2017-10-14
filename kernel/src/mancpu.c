/*
 * mancpu.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"mancpu.h"
#include<DOS.H>
#include"mancolas.h"
#include"datos.h"

bool first_run = false;
int torun;
PCB main_pp;
int running_pcb;
void interrupt(*timer_handler_old)
(void);
/* nuevo interrupt handler del timer */
void interrupt timer_handler_new() {
	disable();
	if (first_run) {
		pcbs[torun].ss = _SS;
		pcbs[torun].sp = _SP;
		pcbs[torun].state = READY;
	} else {
		main_pp.ss = _SS;
		main_pp.sp = _SP;
		main_pp.state = READY;
		main_pp.name = "main";
		/*inserta(&main_pp, listos); */
	}
	torun = obtener_primero();
	if (first_run) {
		inserta(running_pcb);
	}

	_SS = pcbs[torun].ss;
	_SP = pcbs[torun].sp;
	pcbs[torun].state = RUNNING;
	running_pcb = torun;
	if (!first_run) {
		first_run = true;
	}
	timer_handler_old();
	enable();
}
