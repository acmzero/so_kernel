/*
 * proc4.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"procesos.h"
#include<GRAPHICS.H>
#include<DOS.H>
#include"libs.h"
#include"pripro.h"

/* mostrar mensaje random */
char *str_m;
void proceso_4() {
	char *messages[] = { "This is a fixed length text",
			"this is the same length   .", "hoy me fue bien en el examen :)" };
	int c_sec = -1;
	struct time t;
	int count, n;
	retrasa(20, false);
	while (1) {
		lee_teclado();
		gettime(&t);
		count = (int) t.ti_sec;
		n = 3;
		if (c_sec != count) {
			c_sec = count;
			disable();
			set_viewport(2);
			setcolor(BLACK);
			outtextxy(10, 10, str_m);
			setcolor(WHITE);
			str_m = messages[count % n];
			outtextxy(10, 10, str_m);
			enable();
		}
	}
}

