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
  WAITING
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
  p->d_x = p->max_x-p->x;
  p->d_y = p->max_y-p->y;
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
  init_job(&proceso_exit, 9);
  running = &pcbs[0];
  waiting = &pcbs[1];
}

/* codigo principal que reemplaza el interrupt handler del timer */
int main(void){
  initialize();

  timer_handler_old = getvect(TIMER_INT);
  setvect(TIMER_INT, timer_handler_new);

  outtextxy(10, 20, "main");
  getch();
  setvect(TIMER_INT, timer_handler_old);
  return 0;
}

/* 'pelota' rebotando en su cuadrante */
void proceso_1(){
  while(1){
  disable();
  set_viewport(0);
  enable();
  delay(100);
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
      sprintf(f_time, "Time: %d:%d:%d", t.ti_hour, t.ti_min, t.ti_sec);
      x = 10;
      y = 10;
      disable();
      set_viewport(1);
      outtextxy( x, y, f_time);
      enable();
      delay(100);
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
      outtextxy(10,10, messages[count%n]);
      enable();
    }
  }
}

/* por implementar */
void proceso_4(){
  outtextxy(10,10, "proceso 4");
  proceso_1();
}
/* cambia el offset de impresion de pantalla por alguno de los cuadros */
void set_viewport(int n){
  point *p = &off_points[n];
  current_view = n;
  setviewport(p->x, p->y, p->max_x, p->max_y, 1);
  setfillstyle(SOLID_FILL, BLACK);
  clearviewport();
}
PCB *aux;
int first_run = 0;
int tick_count =0;
int turn = 0;
PCB *get_next(){
  int n = 3;
  turn +=1;
  turn = turn%n;
  if(turn==0){
    return &pcbs[1];
  }
  if(turn==1){
    return &pcbs[2];
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
