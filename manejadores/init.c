#include "primitivas/pripro.h"
#include "manejadores/man_cpu.h"

void init_kernel(void){
  activa(&proceso_1);
  activa(&proceso_6);

  timer_handler_old = getvect(0x8);
  setvect(0x8, timer_handler_new);
  
  while(1){ }
}
