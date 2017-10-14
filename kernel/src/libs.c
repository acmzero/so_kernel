/*
 * libs.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#include"libs.h"
#include"datos.h"
#include<GRAPHICS.H>

static point off_points[5];
/* cambia el offset de impresion de pantalla por alguno de los cuadros */
void set_viewport(int n) {
	point p = off_points[n];
	setviewport(p.x, p.y, p.max_x, p.max_y, 1);
}
/* utileria para inicializar puntos y rectangulos en pantalla */
void set_off_point(int n, int x, int y, int max_x, int max_y) {
	point p = off_points[n];
	p.x = x + 1;
	p.y = y + 1;
	p.max_x = max_x - 1;
	p.max_y = max_y - 1;
	p.d_x = p.max_x - p.x - 5;
	p.d_y = p.max_y - p.y - 10;
}

