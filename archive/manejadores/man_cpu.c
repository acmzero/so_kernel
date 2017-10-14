
PCB *torun;
void interrupt timer_handler_new(){
  disable();
  /* ignora primer _SS y _SP correspondientes a main */
  if(first_run){
    /* guarda SS y SP del proceso en ejecucion */
    torun->ss = _SS;
    torun->sp = _SP;
    torun->state = READY;
  }
  
  torun = obten_primero();

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
