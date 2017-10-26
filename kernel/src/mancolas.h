/*
 * mancolas.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

#ifndef MANCOLAS_H_
#define MANCOLAS_H_
#include"datos.h"
#include"pripro.h"
#include"queue.h"
#include"llist.h"
#include<DOS.H>

#define NULL_ENTRY -1
#define COLAS_SIZE 5

extern void inicializa_colas();
extern void inserta(int n);
extern void sacar(int n);
extern int obtener_primero();
extern void mete_cola_retrasa(int time);

extern queue listos[];
extern l_list *lista_retrasa;
extern bool cola_retrasa_initialized;

#endif /* MANCOLAS_H_ */
