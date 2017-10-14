/*
 * autores Roberto, Heli
 * 
 * Reemplaza el interruptor del timer por nuestra funcion
 * la cual muestra la hora actual cada N ticks del timer.
 */
#include "dos.h"
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <setjmp.h>
#define TIMER_ADDRESS 0x8
#define TICKS_TO_PRINT 10
#define EXIT_KEY 0x1B
#define READY_STATUS 0x1 
#define WAITING_STATUS 0x2 
#define RUNNING_STATUS 0x0

typedef void (*job_definition)(void);


typedef struct {
  int id;
  int status;
  unsigned cs;
  unsigned ip;
  char *name;
  jmp_buf state;
  int int_state;
} PCB;

typedef struct {
   PCB *value;
   PCB *next;
} list_entry;

typedef struct {
   list_entry *head;
   list_entry *tail;
} queue;

queue ready_q;
PCB *running;

void interrupt (*old_timer_function)();
PCB *initialize_job(char *job_name, job_definition *job);
void show_current_time();
void show_hello_world();
void save_job_state(PCB *job);
void activate_job(PCB *job);
void print_jobs(queue *q);
int timer_counter = 0;

int job_sequence = 0;

void draw_squares(){
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "o:\\tc\\bgi");
  int x = getmaxx();
  int y = getmaxy();
  int m_x = x/2;
  int m_y = y/2;

  line(0, m_y, x, m_y);
  closegraph();
  
}
void initialize_stucts(){
  ready_q.head = NULL;
  running = NULL;
  draw_squares();
}
/*
 * Gets and remove an item from the queue "q" 
 * returning the pointer to the removed item
 */
PCB *get_next_job(queue q){
  list_entry *next = q.head;
  PCB *pcb;
  if(next != NULL){
    q.head = (list_entry*)next->next;
    pcb = next->value;
  }

  return pcb;
}
/*
 * Adds an item to the last position of "q"
 */
void add_job(queue *q, PCB *p){
  if(q->tail != NULL){
    q->tail->next = p;
    q->tail->value = p;
  }
}
void interrupt new_timer_function(void){
  old_timer_function();
}
void interrupt new_timer_function1(void){
  /* gets next job to run */
  PCB *next_job = get_next_job(ready_q);
  if(running != NULL){
    /* if next job is the same as running, return it to the queue tail */
    if(running->id == next_job->id){
      add_job(&ready_q, next_job);
      next_job = NULL;
    }
  }

  if(next_job != NULL){
    /* save state of current job */
    save_job_state(running);
    /* run next_job */
    activate_job(next_job);
  }
  

  /* ejecutamos el codigo original del handler*/
  old_timer_function();
}
void show_current_time(void){
    /* estructura para guardar el tiempo actual, definido dentro de dos.h */
    struct time t;
    gettime(&t);
    /* limpia el contenido de la pantalla */
    clrscr(); /* dentro de conio.h */
    /*imprime la hora actual*/
    printf("Time: %d:%d:%d\n", t.ti_hour, t.ti_min, t.ti_sec);
}
void show_hello_world(void){
    while(1){
    clrscr();
    printf("Hello World!");
    }
}

int main(void){
  initialize_stucts();
  /*obtener dato de direccion de timer*/
  /* y guardarlo en una funcion nuestra*/
  old_timer_function = getvect(TIMER_ADDRESS);
  /*reemplazar la direccion de la funcion original con la nuestra*/
  setvect(TIMER_ADDRESS, new_timer_function);


  /*initialize_job("Hola Mundo", (job_definition*)show_hello_world);
  print_jobs(&ready_q);  */
  /*evita que el programa termine y asi tener alguna manera de regresar la 
   * funcion original al timer*/
  /* ademas al presionar la tecla EXIT_KEY (escape)  termina la ejecucion */
  while(!kbhit() && (getch() != EXIT_KEY)){};
  
  /*regresa la funcion original a la direccion del timer*/
  setvect(TIMER_ADDRESS, old_timer_function);
  return 0;
}


/*
 * Obtendra el puntero a un metodo y lo convertira en PCB,
 * retornando el puntero del PCB nuevo
 */
PCB *initialize_job(char *job_name, job_definition *job_ptr){
  PCB job_pcb;
  job_pcb.name = job_name;
  job_pcb.cs = FP_SEG(job_ptr);
  /* como obtengo el ip? */
  job_pcb.ip = FP_OFF(job_ptr);
  job_pcb.id = job_sequence;
  job_sequence = job_sequence + 1;
  job_pcb.status = READY_STATUS;


  if(ready_q.head == NULL){
    list_entry t;
    t.next = NULL;
    t.value = &job_pcb;
    ready_q.head = &t;
  }
  return &job_pcb;
}
void save_job_state(PCB *job){
  job->int_state = setjmp(job->state);
}
void activate_job(PCB *job){
  if(job->state != NULL){
    /*longjmp(job->state, job->int_state); */
  }
}
void print_jobs(queue *q){
  list_entry *e;
  if(q->head != NULL){
    e = q->head;
    while(e!=NULL){
      printf(e->value->name);
      e = (list_entry*)e->next;
    }
  }
}
