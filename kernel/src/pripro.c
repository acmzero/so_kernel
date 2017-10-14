/*
 * pripro.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include<DOS.H>
#include<ALLOC.H>
#include"datos.h"
#include"mancolas.h"
#include"pripro.h"



PCB pcbs[PCBS_SIZE];
int pcb_count;
void activa(void (*jobptr), char *name) {
	PCB *pcb = malloc(sizeof(PCB));
	regs *ct = (regs*) pcb->stack + STACK_SIZE - sizeof(regs);

	pcb->id = pcb_count;
	pcb->state = READY;
	pcb->name = name;
	pcb->ss=FP_SEG((regs far *) ct);
	pcb->sp=FP_OFF((regs far *) ct);

	ct->ds = _DS;
	ct->es = _ES;
	ct->cs = FP_SEG(jobptr);
	ct->ip = FP_OFF(jobptr);
	ct->flags = 0x200;
	pcb_count = pcb_count+1;
	inserta(pcb, listos);
}

void elimina(){
	saca(&running_pcb, listos);
	running_pcb.state = TERMINATED;
}

