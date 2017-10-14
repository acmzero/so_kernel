typedef struct {
  PCB *value;
  cola_entry *next;
} cola_entry;

typedef struct {
  cola_entry *head;
  cola_entry *tail;
} cola;

void inserta(PCB *p, cola *q);
void saca(PCB *p, cola *q);
cola_entry obten_primero(cola *q);

cola listos;
