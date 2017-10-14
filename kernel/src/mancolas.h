/*
 * mancolas.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"datos.h"

#ifndef MANCOLAS_H_
#define MANCOLAS_H_

struct cola_ent {
	PCB *value;
	struct cola_ent *next;
};

typedef struct cola_ent cola_entry;

typedef struct {
	cola_entry *head;
} cola;

extern void inserta(PCB *pcb, cola *q);
extern void sacar(PCB *pcb, cola *q);
extern cola_entry *obtener_primero(cola *q);

extern cola *listos;

#endif /* MANCOLAS_H_ */
