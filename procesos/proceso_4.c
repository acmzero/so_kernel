/* mostrar mensaje random */
void proceso_4(){
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
      c_sec = count;
      disable();
      set_viewport(2);
      bar(10,10,300,100);
      outtextxy(10,10, messages[count%n]);
      enable();
    }
  }
}
