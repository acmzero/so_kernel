/*
 * datos.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#ifndef DATOS_H_
#define DATOS_H_

#define STACK_SIZE 2048
#define PCBS_SIZE 10
#define ESC_KEY 0x1B

typedef enum {
	READY, RUNNING, WAITING, TERMINATED
} PSTATE;

typedef struct {
	int id;
	char *name;
	unsigned ss;
	unsigned sp;
	PSTATE state;
	char stack[STACK_SIZE];
	char dummy;
	char dummy2;
} PCB;

extern PCB pcbs[];
extern int running_pcb;
extern int pcb_count;

typedef struct {
	unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
} regs;

typedef enum {
	false, true
} bool;

extern bool esc_pressed;
extern bool has_key;
extern char key_c;

extern int MAX_X, MAX_Y;
extern int MID_X, MID_Y;

extern bool graphics_itinialized;

#endif /* DATOS_H_ */

#ifndef NULL
#define NULL 0
#endif
