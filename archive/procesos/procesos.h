#define OFF_X 160
#define OFF_Y 160

typedef struct {
  int x,y;
} point;

void proceso_1();
void proceso_2();
void proceso_3();
void proceso_4();
void proceso_5();
void proceso_6();


/* selecciona el cuadrante a imprimir */
void set_viewport(int n);

/* for temporal key handler */
int has_key=0;
char key;
