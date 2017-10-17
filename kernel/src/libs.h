/*
 * libs.h
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */

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


#endif /* LIBS_H_ */
