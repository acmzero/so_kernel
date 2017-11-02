/*
 * mancpu.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"datos.h"
#include<DOS.H>
#ifndef MANCPU_H_
#define MANCPU_H_

extern void interrupt (*timer_handler_old)(void);
extern void interrupt timer_handler_new(void);
extern void  increase_timer_freq(void);
extern void  procesa_retrasa(void);

#endif /* MANCPU_H_ */
