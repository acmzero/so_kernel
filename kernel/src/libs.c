/*
 * libs.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#include"libs.h"
#include"datos.h"
#include<GRAPHICS.H>
#include<DOS.H>

point off_points[5];
/* cambia el offset de impresion de pantalla por alguno de los cuadros */
void set_viewport(int n) {
	point p = off_points[n];
	setviewport(p.x, p.y, p.max_x, p.max_y, 1);
}
/* utileria para inicializar puntos y rectangulos en pantalla */
void set_off_point(int n, int x, int y, int max_x, int max_y) {
	off_points[n].x = x + 1;
	off_points[n].y = y + 1;
	off_points[n].max_x = max_x - 1;
	off_points[n].max_y = max_y - 1;
	off_points[n].d_x = off_points[n].max_x - off_points[n].x - 5;
	off_points[n].d_y = off_points[n].max_y - off_points[n].y - 10;
}

