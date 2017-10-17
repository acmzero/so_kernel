/*
 * pripro.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

#ifndef PRIPRO_H_
#define PRIPRO_H_

typedef void(*jobptr)();

extern void activa(void (*jobptr), char *);
extern void elimina();
extern void lee_teclado();


#endif /* PRIPRO_H_ */
