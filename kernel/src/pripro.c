/*
 * pripro.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"pripro.h"
#include<DOS.H>
#include"datos.h"
#include"mancolas.h"
#include"mancpu.h"

#define DEFAULT_PRIORITY 0

PCB pcbs[PCBS_SIZE];
int pcb_count = 1;
void activa(void (*jobptr), char *name) {
	regs *ct = (regs*) pcbs[pcb_count].stack + STACK_SIZE - sizeof(regs);
	pcbs[pcb_count].id = pcb_count;
	pcbs[pcb_count].state = READY;
	pcbs[pcb_count].name = name;
	pcbs[pcb_count].priority = DEFAULT_PRIORITY;
	pcbs[pcb_count].ss=FP_SEG((regs far *) ct);
	pcbs[pcb_count].sp=FP_OFF((regs far *) ct);

	ct->ds = _DS;
	ct->es = _ES;
	ct->cs = FP_SEG(jobptr);
	ct->ip = FP_OFF(jobptr);
	ct->flags = 0x200;
	inserta(pcb_count);
	pcb_count++;
}

void elimina() {
	sacar(running_pcb);
	pcbs[running_pcb].state = TERMINATED;
	timer_handler_new();
}

char str_log_pripro[40];
void retrasa(int time, bool test) {
	if (tiempo_retrasa > time) {
		tiempo_retrasa = time;
	}
	sprintf(str_log_pripro, "[inserting] %s %d\n", pcbs[running_pcb].name,
			time);
	log_line(str_log_pripro);
	sacar(running_pcb);
	pcbs[running_pcb].state = DELAYED;
	if (!test) {
		mete_cola_retrasa(time + 1);
		timer_handler_new();
	} else {
		mete_cola_retrasa(time);
	}
}
