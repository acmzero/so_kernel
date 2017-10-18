/*
 * mancpu.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
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
	} else {
		main_pp.ss = _SS;
		main_pp.sp = _SP;
		main_pp.state = READY;
		main_pp.name = "main";
		main_pp.id = pcb_count;
		pcbs[pcb_count] = main_pp;
		pcb_count++;
		inserta(main_pp.id, &listos);
	}
	torun = obtener_primero(&listos);
	if (first_run) {
		inserta(running_pcb, &listos);
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
