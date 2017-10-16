/*
 * proc2.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */
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
void move_ball(int bn, point limit) {
	int mx, my;
	int ax, ay;
	char str[32];
	ball b = balls[bn];
	int speed = 1;
	point p = b.p;
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

	sprintf(str, "%d %d %d %d %d %d", ax, ay, b.p.x, b.p.y, limit.d_x,
			limit.d_y);
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
		move_ball(bn, limit);
	} else {
		/* movement possible, erase previous char and put new x,y,char */
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

void proceso_2() {
	point limit;
	balls[0].p.x = 30;
	balls[0].p.y = 55;
	balls[0].clockwise = -1;
	balls[0].c = '0';
	balls[0].direction = 1;
	balls[0].dir_change_count = 0;
	limit.x = MID_X - 7;
	limit.y = MID_Y - 7;
	while (1) {
		move_ball(0, limit);
		delay(3);
	}
}

