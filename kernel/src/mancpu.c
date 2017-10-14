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
PCB *torun;
PCB main_pp;
PCB running_pcb;
/* nuevo interrupt handler del timer */
void interrupt timer_handler_new() {
	disable();
	printf("context_\n");
	/* ignora primer _SS y _SP correspondientes a main */
	if(first_run) {
		/* guarda SS y SP del proceso en ejecucion */
		torun->ss = _SS;
		torun->sp = _SP;
		torun->state = READY;
	} else {
		/* save init.main state */
		main_pp.ss = _SS;
		main_pp.sp = _SP;
		main_pp.state = READY;
		main_pp.name = "main";
		/*inserta(&main_pp, listos); */
	}

	torun = obtener_primero(listos)->value;
	printf("next to run %s\n", torun->name );

	/* asigna SS y SP del nuevo proceso */
	_SS = torun->ss;
	_SP = torun->sp;
	torun->state = RUNNING;
	if(!first_run) {
		first_run = true;
	}
	timer_handler_old();
	enable();
}
