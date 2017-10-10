

void inserta(PCB *p, cola *q){
  cola_entry e;
    e->value = p;
    e->next = NULL;
  if(q->head == NULL){
    q->head = e;
    q->tail = e;
  }else{
    q->tail.next = e;
    q->tail = e;
  }
}

cola_entry obten_primero(cola *q){
  return q->head;
}

void saca(PCB *p, cola *q){
  cola_entry e, prev;
  e = q->head;
  while(e != NULL){
    if(e.value == p){
      prev.next = e.next;
      return;
    }
    prev = e;
    e = e.next;
  }
}
