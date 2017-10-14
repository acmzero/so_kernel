/* mostrar hora */
void proceso_3(){
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
      bar(x, y, 200, 200);
      outtextxy(x,y, f_time);
      enable();
      delay(1);
    }
  }
}
