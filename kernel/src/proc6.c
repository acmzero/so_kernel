/*
 * proc6.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#include"mancpu.h"
#include"datos.h"
#include<DOS.H>

bool has_key = false;
bool esc_pressed = false;
char key_c;
/* se perdio SS y SP de main, emular main en un nuevo proceso */
void proceso_6() {
	char c;
	while (1) {
		if (kbhit()) {
			c = getch();
			if (c == ESC_KEY) {
				setvect(0x8, timer_handler_old);
				exit(1);
			} else {
				disable();
				has_key = true;
				key_c = c;
				enable();
			}
		}
	}
}
