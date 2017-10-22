/*
 * libs.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

#include"datos.h"
#include"mancolas.h"
#include<GRAPHICS.H>
#ifndef LIBS_H_
#define LIBS_H_


typedef struct {
  int x,y;
  int max_x, max_y;
  int d_x, d_y;
} point;


extern void set_viewport(int n);
extern void set_off_point(int n, int x, int y, int max_x, int max_y);
extern point off_points[];
extern void lee_teclado();
extern void inicializa_pantalla();
extern void print_line(int vp, int x, int y, char *ss, int col);

extern bool esc_pressed;
extern bool has_key;
extern char key_c;

extern int MAX_X, MAX_Y;
extern int MID_X, MID_Y;

extern bool graphics_itinialized;

extern queue teclado;
extern bool teclado_inicializado;


#endif /* LIBS_H_ */
