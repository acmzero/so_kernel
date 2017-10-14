/*
 * pripro.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#ifndef PRIPRO_H_
#define PRIPRO_H_

typedef void(*jobptr)();

extern void activa(void (*jobptr), char *);
extern void elimina();

#endif /* PRIPRO_H_ */
