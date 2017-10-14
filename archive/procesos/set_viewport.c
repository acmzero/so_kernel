
point off_points[4];
int off_initiated = 0;
/* utileria para inicializar puntos y rectangulos en pantalla */

void set_off_point(int n, int x, int y, int max_x, int max_y){
  point *p = &off_points[n];
  p->x = x+1;
  p->y = y+1;
}
void init_off_points(){
  if(!off_initiated){
    int x,y, m_x, m_y;
    x = getmaxx();
    y = getmaxy();
    m_x = x/2;
    m_y = y/2;
    set_off_point(0, 0, 1, m_x, m_y);
    set_off_point(1, m_x, 1, x, m_y);
    set_off_point(2, 0, m_y+1, m_x, y);
    set_off_point(3, m_x, m_y+1, x, y);
    off_initiated = 1;
  }
}
void set_viewport(int n){
  init_off_points();
  point p = off_points[n];
  setviewport(p.x, p.y, p.x+OFF_X, p.y+OFF_Y, 1);
}
