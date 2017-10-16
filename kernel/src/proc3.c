/*
 * proc3.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include<GRAPHICS.H>
#include<DOS.H>
#include"libs.h"
#include"pripro.h"

/* mostrar hora */
void proceso_3() {
	char f_time[30];
	struct time t;
	int x, y;
	while (1) {
		lee_teclado();
		gettime(&t);
		disable();
		set_viewport(1);
		x = 10;
		y = 10;
		setcolor(BLACK);
		outtextxy(x, y, f_time);
		sprintf(f_time, "Time: %02d:%02d:%02d.%02d", t.ti_hour, t.ti_min,
				t.ti_sec, t.ti_hund);
		setcolor(WHITE);
		outtextxy(x, y, f_time);
		enable();
	}
}
