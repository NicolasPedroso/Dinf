#include <stdlib.h>
#include "Pistola.h"

pistola* criaPistola(){

	pistola *novaPistola = (pistola*) malloc(sizeof(pistola));
	if (!novaPistola) return NULL;
	novaPistola->tempo = 0;
	novaPistola->tiros = NULL;
	return novaPistola;
}

bala* tiroPistola(unsigned short x, unsigned short y, unsigned char trajetoria, pistola *arma){
	
	bala *novaBala = criaBala(x, y, trajetoria, arma->tiros);
	if (!novaBala) return NULL;
	return novaBala;
}

void destroiPistola(pistola *elemento){

	bala *sentinela;
	for (bala *id = elemento->tiros; id != NULL; id = sentinela){
		sentinela = (bala*) id->prox;
		destroiBala(id);
	}
	free(elemento);
}