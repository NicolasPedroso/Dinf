#include <stdlib.h>
#include "Bala.h"

bala* criaBala(unsigned short x, unsigned short y, unsigned char trajetoria, bala *prox){

	if ((trajetoria < 0) || (trajetoria > 1)) return NULL;

	bala *novaBala = (bala*) malloc(sizeof(bala));
	if (!novaBala) return NULL;
	novaBala->x = x;
	novaBala->y = y;
	novaBala->trajetoria = trajetoria;
	novaBala->prox = (struct bala*) prox;
	return novaBala;
}

void moveBala(bala *elementos){

	for (bala *id = elementos; id != NULL; id = (bala*) id->prox){
		if (!id->trajetoria) id->x = id->x - MOVI_BALA;
		else id->x = id->x + MOVI_BALA;
	}
}

void destroiBala(bala *elemento){

	free(elemento);
}