/*
 * autores Heli Villarreal, Roberto Mieres
 * Reemplaza el interrupt handler del timer 
 * por nuestra implementacion para poder simular
 * multitareas
 */
#include <graphics.h>
#include <dos.h>
#include <alloc.h>

#define TIMER_INT 0x8
#define STACK_SIZE 2048

typedef void (*job);
typedef void(*jobptr)();
void interrupt (*timer_handler_old)();
void interrupt timer_handler_new();
void init_job(void(*job)(void), int n);

void proceso_1();
void proceso_2();
void proceso_3();
void proceso_exit();
void set_viewport(int n);

typedef struct {
  int x,y;
  int max_x, max_y;
  int d_x, d_y;
} point;


typedef enum  {
  READY,
  RUNNING,
  WAITING,
  TERMINATED
  
} PSTATE;
typedef struct 
{
	unsigned bp, 
		 di, 
		 si, 
		 ds, 
                 es,
                 dx, 
                 cx, 
                 bx, 
                 ax,
                 ip, 
                 cs, 
                 flags;
} regs;
typedef struct {
  int id;
  char *name;
  unsigned ss;
  unsigned sp;
  PSTATE state;
  char stack[STACK_SIZE];
  char dummy;
  char dummy2;
} PCB;

point *off_points; 
int current_view;
/* array para cola de procesos */
PCB *pcbs;
PCB *running;
PCB *waiting;

/* utileria para inicializar puntos y rectangulos en pantalla */
void set_off_point(int n, int x, int y, int max_x, int max_y){
  point *p = &off_points[n];
  p->x = x+1;
  p->y = y+1;
  p->max_x = max_x-1;
  p->max_y = max_y-1;
  p->d_x = p->max_x-p->x-5;
  p->d_y = p->max_y-p->y-10;
}
void proceso_4();

/*
 * Inicializa la pantalla, procesos y PCB a ejecutar
 */
void initialize(){
  int  gd = DETECT, gm;
  int x,y, m_x, m_y;
  running = NULL;
  waiting = NULL;
  off_points = (point*) malloc(4*sizeof(point));
  pcbs = (PCB*) malloc(10*sizeof(PCB));
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

  init_job(&proceso_1, 0);
  init_job(&proceso_2, 1);
  init_job(&proceso_3, 2);
  init_job(&proceso_4, 3);
  init_job(&proceso_exit, 9);
  running = &pcbs[0];
  waiting = &pcbs[1];
}

/* codigo principal que reemplaza el interrupt handler del timer */
int main(void){
  initialize();

  timer_handler_old = getvect(TIMER_INT);
  setvect(TIMER_INT, timer_handler_new);

  getch();
  setvect(TIMER_INT, timer_handler_old);
  return 0;
}


/* 'pelota' rebotando en su cuadrante */
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
  if(ax>= limit.d_x || ax<0
      || ay >= limit.d_y || ay < 0){
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
void proceso_1(){
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

  while(1){
    disable();
    set_viewport(0);
    move_ball(b1, off_points[0]);
    move_ball(b2, off_points[0]);
    enable();
    delay(1);
  }
}

/* mostrar hora */
void proceso_2(){
  int c_sec = -1;
  while(1){
    struct time t;
    char *f_time;
    int x,y, sec;
    gettime(&t);
    sec = (int)t.ti_sec;
    if(c_sec!=sec){
      c_sec = sec;
      f_time = (char*) malloc( 15*sizeof(char));
      sprintf(f_time, "Time: %02d:%02d:%02d", t.ti_hour, t.ti_min, t.ti_sec);
      x = 10;
      y = 10;
      disable();
      set_viewport(1);
      bar(x,y,200,200);
      outtextxy( x, y, f_time);
      enable();
      delay(1);
    }
  }
}
/* mostrar mensaje random */
void proceso_3(){
  char *messages[] = {
    "This is a fixed length text",
    "this is the same length   .",
    "hoy me fue bien en el examen :)"
  };
  int c_sec = -1;
  while(1){
    struct time t;
    int count, n;
    gettime(&t);
    count = (int)t.ti_sec;
    n = 3;
    if(c_sec!=count){
      disable();
      c_sec = count;
      set_viewport(2);
      bar(10,10,300,100);
      outtextxy(10,10, messages[count%n]);
      enable();
    }
  }
}

/* por implementar */
void proceso_4(){
  char mat[40][40], c, str[2];
  point p;
  int text_size = 10;
  int first_done = 0;
  p.x=0;
  p.y=0;
  while(1){
    if(kbhit() && (c =getch())!= 0x1B){
      disable();
      set_viewport(3);
      if(c==0x8){
        p.x--;
        if(p.x<0){
          p.x=32;
          p.y--;
        }
        if(p.y<0){
          p.y=23;
        }
      }
      if(first_done || c==0x8){
        setcolor(BLACK);
        sprintf(str, "%c", mat[p.x][p.y]);
        outtextxy(p.x*text_size,p.y*text_size, str);
        setcolor(WHITE);
      }
      if(c!=0x8){
        sprintf(str, "%c", c);
        outtextxy(p.x*text_size,p.y*text_size, str);
        mat[p.x][p.y] = c;
        p.x++;
        if(p.x>=32){
          p.y++;
          p.x=0;
          if(p.y>=24){
            p.y=0;
            first_done = 1;
          }
        }
      }
      enable();
    }
  }
}
/* cambia el offset de impresion de pantalla por alguno de los cuadros */
void set_viewport(int n){
  point *p = &off_points[n];
  current_view = n;
  setviewport(p->x, p->y, p->max_x, p->max_y, 1);
  setfillstyle(SOLID_FILL, BLACK);
   /*clearviewport();  */
}
PCB *aux;
int first_run = 0;
int tick_count =0;
int turn = 0;
PCB *get_next(){
  int n = 5;
  turn +=1;
  turn = turn%n;
  if(turn==0){
    return &pcbs[1];
  }
  if(turn==1){
    return &pcbs[2];
  }
  if(turn==2){
    return &pcbs[0];
  }
  if(turn==3){
    return &pcbs[3];
  }
  return &pcbs[9];
}
PCB *torun;
/* nuevo interrupt handler del timer */
void interrupt timer_handler_new(){
  disable();
  /* ignora primer _SS y _SP correspondientes a main */
  if(first_run){
    /* guarda SS y SP del proceso en ejecucion */
    torun->ss = _SS;
    torun->sp = _SP;
    torun->state = READY;
  }
  
  torun = get_next();

  /* asigna SS y SP del nuevo proceso */
  _SS = torun->ss;
  _SP = torun->sp;
  torun->state = RUNNING;
  if(!first_run){
    first_run = 1;
  }
  timer_handler_old();
  enable();
}
void init_job(jobptr j, int n){
  PCB *pcb = &pcbs[n];
  regs *ct = (regs*) pcb->stack + STACK_SIZE - sizeof(regs);

  pcb->id = n;
  pcb->state = READY;
  pcb->ss=FP_SEG((regs far *) ct);
  pcb->sp=FP_OFF((regs far *) ct);

  ct->ds = _DS;
  ct->es = _ES;
  ct->cs = FP_SEG(j);
  ct->ip = FP_OFF(j);
  ct->flags = 0x200;
}

/* se perdio SS y SP de main, emular main en un nuevo proceso */
void proceso_exit(){
  while(1){
    if(kbhit()){
      if(getch() == 0x1B){
        setvect(TIMER_INT, timer_handler_old);
        exit(1);
      }
    }
  }
}
