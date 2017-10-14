/*
 * pripro.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include<DOS.H>
#include"datos.h"
#include"mancolas.h"
#include"pripro.h"



PCB pcbs[PCBS_SIZE];
int pcb_count=0;
void activa(void (*jobptr), char *name) {
	regs *ct = (regs*) pcbs[pcb_count].stack + STACK_SIZE - sizeof(regs);
//	printf("pcb_count %d\n",pcb_count);

	pcbs[pcb_count].id = pcb_count;
	pcbs[pcb_count].state = READY;
	pcbs[pcb_count].name = name;
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

void elimina(){
	sacar(running_pcb);
	pcbs[running_pcb].state = TERMINATED;
	timer_handler_new();
}

