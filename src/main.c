/*
 * autores Roberto, Heli
 * 
 * Reemplaza el interruptor del timer por nuestra funcion
 * la cual muestra la hora actual cada N ticks del timer.
 *
 *
 */
#include "dos.h"
#include <conio.h>
#include <stdio.h>
#define TIMER_ADDRESS 0x8
#define TICKS_TO_PRINT 10
#define EXIT_KEY 0x1B

void interrupt (*old_timer_function)();
void show_current_time();
int timer_counter = 0;
void interrupt new_timer_function(void){
  /* ejecutamos el codigo original del handler*/
  old_timer_function();
  /* actualizamos el contador cada tick */
  timer_counter = timer_counter + 1;
  /* cada TICKS_TO_PRINT actualizamos el tiempo */
  if(timer_counter%TICKS_TO_PRINT == 0){
    /* mostrar tiempo actual */
    show_current_time();
  }
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

int main(void){
  /*obtener dato de direccion de timer*/
  /* y guardarlo en una funcion nuestra*/
  old_timer_function = getvect(TIMER_ADDRESS);
  /*reemplazar la direccion de la funcion original con la nuestra*/
  setvect(TIMER_ADDRESS, new_timer_function);

  /*evita que el programa termine y asi tener alguna manera de regresar la 
   * funcion original al timer*/
  /* ademas al presionar la tecla EXIT_KEY (escape)  termina la ejecucion */
  while(!kbhit() && (getch() != EXIT_KEY)){};

  /*regresa la funcion original a la direccion del timer*/
  setvect(TIMER_ADDRESS, old_timer_function);
  return 0;
}
