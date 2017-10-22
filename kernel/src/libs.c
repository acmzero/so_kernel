/*
 * libs.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

#include"libs.h"
#include"datos.h"
#include"queue.h"
#include<GRAPHICS.H>
#include<DOS.H>

bool has_key = false;
bool esc_pressed = false;
char key_c;
int MAX_X = 0, MAX_Y = 0;
int MID_X = 0, MID_Y = 0;
bool graphics_itinialized = false;
point off_points[5];
queue teclado;
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

bool teclado_inicializado = false;
void lee_teclado() {
	if (!teclado_inicializado) {
		init_queue(&teclado);
		teclado_inicializado = true;
	}
	if (kbhit()) {
		key_c = getch();
		if (key_c == ESC_KEY) {
			esc_pressed = true;
		} else {
			has_key = true;
			enqueue(key_c, &teclado);
		}
	}
}

void inicializa_pantalla() {
	int gd = DETECT, gm;
	int x, y, m_x, m_y;
	initgraph(&gd, &gm, "c:\\turboc3\\bgi");
	graphics_itinialized = true;
	x = getmaxx();
	y = getmaxy();
	MAX_X = x;
	MAX_Y = y;
	m_x = x / 2;
	m_y = y / 2;
	MID_X = m_x;
	MID_Y = m_y;
	line(m_x, 0, m_x, y);
	line(0, m_y, x, m_y);
	set_off_point(0, 0, 1, m_x, m_y);
	set_off_point(1, m_x, 1, x, m_y);
	set_off_point(2, 0, m_y + 1, m_x, y);
	set_off_point(3, m_x, m_y + 1, x, y);
}

void print_line_old(int vp, int x, int y, char *ss) {
	print_line(vp, x, y, ss, WHITE);
}

void print_line(int vp, int x, int y, char *ss, int col) {
	disable();
	set_viewport(vp);
	setcolor(col);
	outtextxy(x, y, ss);
	enable();
}
