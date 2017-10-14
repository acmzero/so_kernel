/*
 * proc6.c
 *
 *  Created on: Oct 12, 2017
 *      Author: heli
 */

#include"mancpu.h"
#include"datos.h"
#include<DOS.H>

/* se perdio SS y SP de main, emular main en un nuevo proceso */
void proceso_6(){
  char c;
  while(1){
    if(kbhit()){
      if((c=getch()) == ESC_KEY){
        setvect(0x8, timer_handler_old);
        exit(1);
      }else{
        disable();
        has_key = 1;
        key_c = c;
        enable();
      }
    }
  }
}
