void proceso_1(){
  int  gd = DETECT, gm;
  int x,y, m_x, m_y;
  activa(&proceso_2);
  activa(&proceso_3);
  activa(&proceso_4);
  activa(&proceso_5);
  elimina(&proceso_1);

  initgraph(&gd,&gm,"c:\\tc\\bgi");
  x = getmaxx();
  y = getmaxy();
  m_x = x/2;
  m_y = y/2;
  line(m_x,0,m_x,y);
  line(0,m_y, x,m_y);
}
