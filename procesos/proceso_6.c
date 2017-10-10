/* se perdio SS y SP de main, emular main en un nuevo proceso */
void proceso_6(){
  char c;
  while(1){
    if(kbhit()){
      if((c=getch()) == 0x1B){
        setvect(0x8, timer_handler_old);
        exit(1);
      }else{
        disable();
        has_key = 1;
        key = c;
        enable();
      }
    }
  }
}
