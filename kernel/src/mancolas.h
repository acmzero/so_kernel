/*
 * mancolas.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"datos.h"
#include"pripro.h"
#include"queue.h"

#ifndef MANCOLAS_H_
#define MANCOLAS_H_

#define NULL_ENTRY -1
#define COLAS_SIZE 5



extern void inicializa_colas();
extern void inserta(int n, queue *q);
extern void sacar(int n, queue *q);
extern int obtener_primero(queue *q);


extern queue listos;

#endif /* MANCOLAS_H_ */
