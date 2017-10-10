typedef struct {
  point p;
  int clockwise;
  int direction;
  char c;
} ball;

void move_ball(ball *b, point limit){
  int mx, my;
  int ax, ay;
  char str[32];
  int speed = 7;
  point p = b->p;
  if(b->direction == 0){
    mx =  speed;
    my = speed;
  }
  if(b->direction == 1){
    mx = -1*speed;
    my = speed;
  }
  if(b->direction == 2){
    mx = -1*speed;
    my = -1*speed;
  }
  if(b->direction == 3){
    mx = 1*speed;
    my = -1*speed;
  }
  ax = b->p.x + mx;
  ay = b->p.y + my;

  sprintf(str,"%d %d %d %d %d %d", ax, ay , b->p.x,b->p.y, limit.d_x, limit.d_y);
  /*outtextxy(b->p.x, b->p.y, str); */
  if(ax >= limit.x || ax < 0
      || ay >= limit.y || ay < 0){
    /* movement not possible because is off screen */
    /* new movement depends on clockwise */
    b->direction = (b->direction+b->clockwise)%4;
    if(b->direction<0){
      b->direction=3;
    }
    move_ball(b, limit);
  }else{
    /* movement possible, erase previous char and put new x,y,char */
    sprintf(str,"%c", b->c);
    setfillstyle(SOLID_FILL, BLACK);
    setcolor(BLACK);
    /*bar(p.x, p.y, p.x+10, p.y+10); */
    outtextxy(b->p.x, b->p.y, str);
    setcolor(WHITE);
    b->p.x = ax;
    b->p.y = ay;
    outtextxy(b->p.x, b->p.y, str);
  }
}

void proceso_2(){
  point limit;
  ball *b1=malloc(sizeof(ball));
  ball *b2 = malloc(sizeof(ball));
  b1->p.x=30;
  b1->p.y=55;
  b1->clockwise = 1;
  b1->c = '0';
  b1->direction = 1;
  b2->p.x=50;
  b2->p.y=73;
  b2->clockwise = -1;
  b2->c = '0';
  b2->direction = 1;
  limit.x = OFF_X;
  limit.y = OFF_Y;
  while(1){
    disable();
    set_viewport(0);
    move_ball(b1, limit);
    move_ball(b2, limit);
    enable();
    delay(1);
  }
}
