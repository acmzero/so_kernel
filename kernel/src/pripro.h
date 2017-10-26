/*
 * pripro.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

#ifndef PRIPRO_H_
#define PRIPRO_H_

#define STACK_SIZE 4096
#define PCBS_SIZE 10

#define MAX_PRIORITY 5

typedef struct {
	unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
} regs;

typedef enum {
	READY, RUNNING, WAITING, TERMINATED
} PSTATE;

typedef struct {
	int id;
	char *name;
	int priority;
	unsigned ss;
	unsigned sp;
	PSTATE state;
	char stack[STACK_SIZE];
} PCB;

typedef void (*jobptr)();

extern void activa(void (*jobptr), char *);
extern void elimina();
extern void retrasa(int time);
extern void  procesa_retrasa(void);

extern PCB pcbs[];
extern int running_pcb;
extern int pcb_count;

#endif /* PRIPRO_H_ */
