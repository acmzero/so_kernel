

void activa(jobptr j){
  PCB *pcb = &pcbs[n];
  regs *ct = (regs*) pcb->stack + STACK_SIZE - sizeof(regs);

  pcb->id = n;
  pcb->state = READY;
  pcb->ss=FP_SEG((regs far *) ct);
  pcb->sp=FP_OFF((regs far *) ct);

  ct->ds = _DS;
  ct->es = _ES;
  ct->cs = FP_SEG(j);
  ct->ip = FP_OFF(j);
  ct->flags = 0x200;

  inserta(pcb, &listos);
}

void elimina(PCB *p, cola *q){
  saca(p, q);
}
