/*
 * mancpu.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancpu.h"
#include<DOS.H>
#include<_NULL.H>
#include"mancolas.h"
#include"datos.h"
#include"libs.h"

bool first_run = false;
int torun;
PCB main_pp;
int running_pcb;
void interrupt(*timer_handler_old)
(void);
char str_retrasa[30];
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
		inserta(main_pp.id);
	}
	tiempo_retrasa--;
	if(graphics_initialized && tiempo_retrasa>=0) {
		print_line(2, 10, 50, str_retrasa, BLACK);
		sprintf(str_retrasa, "Current tiempo_retrasa %d", tiempo_retrasa);
		print_line(2, 10, 50, str_retrasa, WHITE);
	}
	if(tiempo_retrasa==0) {
		saca_retrasa();
	}
	sacar(running_pcb);
	if (first_run && pcbs[running_pcb].state == RUNNING) {
		inserta(running_pcb);
	}
	torun = obtener_primero(&listos);

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

void increase_timer_freq(void) {
//	int countdown;
//	countdown = 0x1000;
//	asm {
//
//		cli;
//		mov
//		al, 00110110b;
//		out
//		43h, al;
//		mov cx, countdown;
//		mov al, cl;
//		out
//		40h, al;
//		mov al, ch;
//		out
//		40h, al;
//		sti;
//	}
}

