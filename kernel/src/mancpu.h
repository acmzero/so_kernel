/*
 * mancpu.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#ifndef MANCPU_H_
#define MANCPU_H_
#include"datos.h"
#include<DOS.H>

extern void interrupt (*timer_handler_old)(void);
extern void interrupt timer_handler_new(void);
extern void  increase_timer_freq(void);

#endif /* MANCPU_H_ */
