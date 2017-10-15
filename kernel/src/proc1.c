/*
 * proc1.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
#include<GRAPHICS.H>
#include"libs.h"
#include"datos.h"
#include"pripro.h"
#include"mancpu.h"
#include"procesos.h"

int MAX_X = 0, MAX_Y = 0;
int MID_X = 0, MID_Y = 0;
bool graphics_itinialized = false;
void proceso_1() {
	int gd = DETECT, gm;
	int x, y, m_x, m_y;
//	activa(&proceso_2, "p2");
	activa(&proceso_3, "p3");
	activa(&proceso_4, "p4");
	activa(&proceso_5, "p5");
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
	elimina();
}

