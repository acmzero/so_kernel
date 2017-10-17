/*
 * proc6.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

#include<DOS.H>
#include"mancpu.h"
#include"datos.h"
#include"pripro.h"

bool has_key = false;
bool esc_pressed = false;
char key_c;

void proceso_6() {
	while(1){
		lee_teclado();
	}
}
