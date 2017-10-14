/*
 * mancpu.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include"datos.h"
#ifndef MANCPU_H_
#define MANCPU_H_

static void interrupt (*timer_handler_old)(void);
extern void interrupt timer_handler_new(void);

#endif /* MANCPU_H_ */
