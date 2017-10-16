/*
 * proc5.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#include<GRAPHICS.H>
#include<DOS.H>
#include"datos.h"
#include"libs.h"
#include"pripro.h"
#include"mancolas.h"

#define ENTER_KEY 0xD
#define BACKSPACE_KEY 0x8

/* editor de texto */
void proceso_5() {
	char mat[40][40], c, str[2];
	int x, y;
	int text_size = 10;
	int first_done = 0;
	x = 0;
	y = 0;
	while (1) {
		lee_teclado();
		if (!is_empty(TECLADO)) {
			disable();
			/*set_viewport(3);
			 outtextxy(10, 10, "aoesuth");*/
			c = obtener_primero(TECLADO);
			set_viewport(3);
			if (c == BACKSPACE_KEY) {
				x--;
				if (x < 0) {
					x = 32;
					y--;
				}
				if (y < 0) {
					y = 23;
				}
			} else if (c == ENTER_KEY) {
				y++;
				x = 0;
			}
			if (first_done || c == 0x8) {
				setcolor(BLACK);
				sprintf(str, "%c", mat[x][y]);
				outtextxy(x * text_size, y * text_size, str);
				setcolor(WHITE);
			}
			if (c != BACKSPACE_KEY && c != ENTER_KEY) {
				sprintf(str, "%c", c);
				outtextxy(x * text_size, y * text_size, str);
				mat[x][y] = c;
				x++;
				if (x >= 32) {
					y++;
					x = 0;
					if (y >= 24) {
						y = 0;
						first_done = 1;
					}
				}
			}
			has_key = false;
			enable();
		}
	}
}
