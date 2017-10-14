/*
 * datos.h
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#ifndef DATOS_H_
#define DATOS_H_

#define STACK_SIZE 10
#define PCBS_SIZE 2048
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

extern PCB pcbs[PCBS_SIZE];
extern PCB running_pcb;

typedef struct {
	unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
} regs;

typedef enum {
	false, true
} bool;

static bool esc_pressed = false;
static bool has_key = false;
static char key_c;

static int MAX_X=0, MAX_Y=0;
static int MID_X=0, MID_Y=0;

#endif /* DATOS_H_ */

#ifndef NULL
#define NULL 0
#endif
