/* por implementar */
void proceso_5(){
  char mat[40][40], c, str[2];
  int x,y;
  int text_size = 10;
  int first_done = 0;
  x=0;
  y=0;
  while(1){
    if(has_key){
      disable();
      c = key;
      set_viewport(3);
      if(c==0x8){
        x--;
        if(x<0){
          x=32;
          y--;
        }
        if(y<0){
          y=23;
        }
      }
      if(first_done || c==0x8){
        setcolor(BLACK);
        sprintf(str, "%c", mat[p.x][p.y]);
        outtextxy(x*text_size, y*text_size, str);
        setcolor(WHITE);
      }
      if(c!=0x8){
        sprintf(str, "%c", c);
        outtextxy(x*text_size, y*text_size, str);
        mat[x][y] = c;
        x++;
        if(x>=32){
          y++;
          x=0;
          if(y>=24){
            y=0;
            first_done = 1;
          }
        }
      }
      has_key = 0;
      enable();
    }
  }
}
