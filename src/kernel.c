#include <graphics.h>
#include <dos.h>
#include <alloc.h>

#define TIMER_INT 0x8

void interrupt (*timer_handler_old)();
void interrupt timer_handler_new();

void proceso_1();
void proceso_2();
void proceso_3();
void set_viewport(int n);

typedef struct {
  int x,y;
  int max_x, max_y;
} point;


point *off_points; 
void set_off_point(int n, int x, int y, int max_x, int max_y){
  point *p = &off_points[n];
  p->x = x+1;
  p->y = y+1;
  p->max_x = max_x-1;
  p->max_y = max_y-1;
}
void proceso_4();

void initialize(){
  int  gd = DETECT, gm;
  int x,y, m_x, m_y;
  off_points = (point*) malloc(4*sizeof(point));
  initgraph(&gd,&gm,"o:\\tc\\bgi");
  x = getmaxx();
  y = getmaxy();
  m_x = x/2;
  m_y = y/2;


  set_off_point(0, 0, 1, m_x, m_y);
  set_off_point(1, m_x, 1, x, m_y);
  set_off_point(2, 0, m_y+1, m_x, y);
  set_off_point(3, m_x, m_y+1, x, y);
  line(m_x,0,m_x,y);
  line(0,m_y, x,m_y);


}

int main(void){
  int count = 0;
  int out_loop = 1;
  initialize();

  timer_handler_old = getvect(TIMER_INT);
  setvect(TIMER_INT, timer_handler_new);



  while(out_loop){
    set_viewport(count%4);
    if(count%4 == 0){
      proceso_1();
    }
    if(count%4 == 1){
      proceso_2();
    }
    if(count%4 == 2){
      proceso_3();
    }
    if(count%4 == 3){
      proceso_4();
    }

    count = count + 1;
    if(kbhit() && (getch() == 0x1B)){
      out_loop = 0;
    }
  };
  setvect(TIMER_INT, timer_handler_old);
  return 0;
}
/* i'm going to use this first process for testing */
void proceso_1(){
  int x = _SS, xp;
  char *s = (char*) malloc(30*sizeof(char));
  char *p;
  sprintf(s, "%d", x);
  p = (char*) malloc(30*sizeof(char));
  xp = _SP;
  sprintf(p, "%d", xp);
  outtextxy(10,30, s);
  outtextxy(10,40, p);
}

/*mostrar hora */
void proceso_2(){
  struct time t;
  char *f_time;
  int x,y;
  gettime(&t);

  f_time = (char*) malloc( 15*sizeof(char));
  sprintf(f_time, "Time: %d:%d:%d", t.ti_hour, t.ti_min, t.ti_sec);
  x = 10;
  y = 10;
  outtextxy( x, y, f_time);
  proceso_1();
}
/*mostrar mensaje random */
void proceso_3(){
  char *messages[] = {
    "This is a fixed length text",
    "this is the same length   .",
    "hoy me fue bien en el examen :)"
  };
  struct time t;
  int count, n;
  gettime(&t);
  count = (int)t.ti_sec;
  n = 3;
  outtextxy(10,10, messages[count%n]);
  proceso_1();
}
void proceso_4(){
  outtextxy(10,10, "proceso 4");
  proceso_1();
}

void set_viewport(int n){
  point *p = &off_points[n];
  setviewport(p->x, p->y, p->max_x, p->max_y, 1);
  clearviewport();
}
void interrupt timer_handler_new(){

  timer_handler_old();
}
