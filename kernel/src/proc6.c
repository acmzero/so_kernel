/*
 * proc6.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#include<DOS.H>
#include"mancpu.h"
#include"datos.h"
#include"pripro.h"

bool has_key = false;
bool esc_pressed = false;
char key_c;
/* se perdio SS y SP de main, emular main en un nuevo proceso */

void proceso_6() {
	while(1){
		lee_teclado();
	}
}

void proceso_60() {
	char c;
	while (1) {
		if (kbhit()) {
			c = getch();
			disable();
			if (c == ESC_KEY) {
				setvect(0x8, timer_handler_old);
				exit(1);
			} else {
				has_key = true;
				key_c = c;
			}
			enable();
		}
	}
}
