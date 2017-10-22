/*
 * mancpu.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"mancpu.h"
#include<DOS.H>
#include"mancolas.h"
#include"datos.h"
#include"libs.h"

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
		inserta(main_pp.id);
	}
	procesa_retrasa();
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

char str_retrasa[40];
void procesa_retrasa() {
	list_node *e;
	if (lista_retrasa.size == 0) {
		return;
	}
	lista_retrasa.head->value--;
	print_line(2, 10, 40, str_retrasa, BLACK);
	sprintf(str_retrasa, "Retrasa actual %s id/tiempo %d/%d",
			pcbs[lista_retrasa.head->id].name, lista_retrasa.head->id,
			lista_retrasa.head->value);
	print_line(2, 10, 40, str_retrasa, WHITE);
	print_list(&lista_retrasa);
	if (lista_retrasa.head->value <= 0) {
		e = remove_head(&lista_retrasa);
		while (e > 0 && e->value == 0) {
			inserta(e->id);
			if (e->next < 0 || e->next->value > 0) {
				break;
			}
			free(e);
			e = remove_head(&lista_retrasa);
		}
	}
}
