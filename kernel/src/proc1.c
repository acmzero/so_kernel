/*
 * proc1.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"procesos.h"
#include"libs.h"
#include"pripro.h"

void proceso_1() {
	inicializa_pantalla();
	activa(&proceso_2, "p2");
	activa(&proceso_3, "p3");
	activa(&proceso_4, "p4");
	activa(&proceso_5, "p5");
	elimina();
}

