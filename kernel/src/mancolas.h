/*
 * mancolas.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"datos.h"

#ifndef MANCOLAS_H_
#define MANCOLAS_H_
#define NULL_ENTRY -1

struct cola_ent {
	int value;
	struct cola_ent *next;
};

typedef struct cola_ent cola_entry;

typedef struct {
	cola_entry *head;
} cola;

extern void inserta(int pcb);
extern void sacar(int n);
extern int obtener_primero();

extern int listos[];
extern int listos_idx;
extern bool cola_initialized;

#endif /* MANCOLAS_H_ */
