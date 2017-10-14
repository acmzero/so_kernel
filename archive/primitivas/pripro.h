typedef void(*jobptr)();

typedef enum  {
  READY,
  RUNNING,
  WAITING,
  TERMINATED
} PSTATE;

typedef struct {
  unsigned bp, di, si, ds, es, dx, 
           cx, bx, ax, ip, cs, flags;
} regs;

typedef struct {
  int id;
  char *name;
  unsigned ss;
  unsigned sp;
  PSTATE state;
  char stack[STACK_SIZE];
  char dummy, dummy2;
} PCB;

void activa(jobptr j);
void elimina(PCB *p, cola *q);
