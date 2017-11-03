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

struct RetrasaNode {
	int id, time;
	struct RetrasaNode *next;
};

typedef struct RetrasaNode *RetrasaListNode;

extern void inicializa_colas();
extern void inserta(int n);
extern void sacar(int n);
extern int obtener_primero();
extern void mete_cola_retrasa(int time);
extern void saca_retrasa();
extern RetrasaListNode createNode(int id, int t);
extern void insertRight(RetrasaListNode prev, int p, int t);

extern queue listos[];

extern RetrasaListNode retrasa_head;
extern int tiempo_retrasa;
extern void actualizaTiempoRetrasa();

#endif /* MANCOLAS_H_ */
