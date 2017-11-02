#include<STDLIB.H>
#include<STDIO.H>
#include"pripro.h"
#include"mancolas.h"
#include"mancpu.h"

int main(void) {
	int proceso, time;
	proceso = 1;
	do {
		printf("Introduce el tiempo para proceso %d: ", proceso);
		scanf("%d", &time);
		if (time >= 0) {
			running_pcb = proceso;
			retrasa(time, true);
			print_retrasa_list();
			proceso = (proceso + 1) % PCBS_SIZE;
		}
	} while (time >= 0);

	printf("Simulando cambios de contexto: \n");
	print_retrasa_list();
	while (tiempo_retrasa > 0) {
		tiempo_retrasa--;
		if (tiempo_retrasa == 0) {
			saca_retrasa();
			print_retrasa_list();
		}
		delay(100);
	}
	getch();

	return 0;
}

