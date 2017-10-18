/*
 * proc2.c
 *
 *      Author: Heli Villarreal, Roberto Mieres
 */
#include"procesos.h"
#include"libs.h"
#include"datos.h"
#include<GRAPHICS.H>
#include<DOS.H>

typedef struct {
	point p;
	int clockwise;
	int direction;
	char c;
	int dir_change_count;
} ball;

ball balls[2];
char str[3];
void move_ball(int bn, point limit, bool first) {
	int mx, my;
	int ax, ay;
	ball b = balls[bn];
	int speed = 1;
	if (!first) {
		return;
	}
	if (b.direction == 0) {
		mx = speed;
		my = speed;
	}
	if (b.direction == 1) {
		mx = -1 * speed;
		my = speed;
	}
	if (b.direction == 2) {
		mx = -1 * speed;
		my = -1 * speed;
	}
	if (b.direction == 3) {
		mx = 1 * speed;
		my = -1 * speed;
	}
	ax = b.p.x + mx;
	ay = b.p.y + my;

	if (ax >= limit.x || ax < 3 || ay >= limit.y || ay < 3) {
		if (ax >= limit.x && ay >= limit.y) {
			b.direction = 2;
		} else if (ax >= limit.x && ay < limit.y) {
			if (b.dir_change_count % 2 == 0) {
				b.direction = 1;
			} else {
				b.direction = 2;
			}
		} else if (ax < limit.x && ay >= limit.y) {
			if (b.dir_change_count % 2 == 0) {
				b.direction = 3;
			} else {
				b.direction = 2;
			}
		} else if (ax <= 3 && ay <= 3) {
			b.direction = 0;
		} else if (ax <= 3 && ay > 3) {
			if (b.dir_change_count % 2 == 0) {
				b.direction = 3;
			} else {
				b.direction = 0;
			}
		} else if (ax > 3 && ay <= 3) {
			if (b.dir_change_count % 2 == 0) {
				b.direction = 1;
			} else {
				b.direction = 0;
			}
		} else if (ax <= 3 && ay >= limit.y) {
			b.direction = 3;
		} else if (ax >= limit.x && ay <= 3) {
			b.direction = 1;
		}

		b.dir_change_count++;
		balls[bn] = b;
		move_ball(bn, limit, false);
	} else {
		sprintf(str, "%c", b.c);
		disable();
		set_viewport(0);
		setcolor(BLACK);
		outtextxy(b.p.x, b.p.y, str);
		setcolor(WHITE);
		b.p.x = ax;
		b.p.y = ay;
		outtextxy(b.p.x, b.p.y, str);
		balls[bn] = b;
		enable();
	}
}

void inicializa_ball(int n) {
	balls[n].p.x = 30;
	balls[n].p.y = 55;
	balls[n].clockwise = -1;
	balls[n].c = '0';
	balls[n].direction = 1;
	balls[n].dir_change_count = 0;
}
void proceso_2() {
	point limit;
	limit.x = MID_X - 7;
	limit.y = MID_Y - 7;
	inicializa_ball(0);
	while (1) {
		lee_teclado();
		move_ball(0, limit, true);
		delay(2);
	}
}

