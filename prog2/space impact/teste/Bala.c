#include <stdlib.h>
#include "Bala.h"

bala* criaBala(unsigned short x, unsigned short y, unsigned char trajetoria, bala *prox){

	if (trajetoria > 7) return NULL;

	bala *novaBala = (bala*) malloc(sizeof(bala));
	if (!novaBala) return NULL;
	novaBala->x = x;
	novaBala->y = y;
	novaBala->trajetoria = trajetoria;
	novaBala->prox = (struct bala*) prox;
	return novaBala;
}

void moveBalas(bala *balas) {
    for (bala *id = balas; id != NULL; id = (bala *) id->prox) {
        switch (id->trajetoria) {
            case DIRECAO_ESQUERDA:
                id->x -= MOVI_BALA;
                break;
            case DIRECAO_DIREITA:
                id->x += MOVI_BALA;
                break;
            case DIRECAO_CIMA:
                id->y -= MOVI_BALA;
                break;
            case DIRECAO_BAIXO:
                id->y += MOVI_BALA;
                break;
            case DIRECAO_ESQUERDA_CIMA:
                id->x -= MOVI_BALA;
                id->y -= MOVI_BALA;
                break;
            case DIRECAO_DIREITA_CIMA:
                id->x += MOVI_BALA;
                id->y -= MOVI_BALA;
                break;
            case DIRECAO_ESQUERDA_BAIXO:
                id->x -= MOVI_BALA;
                id->y += MOVI_BALA;
                break;
            case DIRECAO_DIREITA_BAIXO:
                id->x += MOVI_BALA;
                id->y += MOVI_BALA;
                break;
            default:
                id->x -= 2;
                break;
        }
    }
}

void destroiBala(bala *elemento){
    if (!elemento) return;

	free(elemento);
}