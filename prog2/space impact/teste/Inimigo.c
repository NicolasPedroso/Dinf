#include <stdlib.h>
#include "Inimigo.h"

inimigo* criaInimigo(unsigned char lado, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y, inimigo *prox){

	if ((x - lado/2 < 0) || (x + lado/2 > max_x) || (y - lado/2 < 0) || (y + lado/2 > max_y)) return NULL;
	if (face > 3) return NULL;

	inimigo *novoInimigo = (inimigo*) malloc(sizeof(inimigo));
	if (!novoInimigo) return NULL;
	novoInimigo->lado = lado;
	novoInimigo->face = face;
	novoInimigo->vida = 3;
	novoInimigo->x = x;
	novoInimigo->y = y;
	novoInimigo->arma = criaPistola();
	novoInimigo->prox = (struct inimigo*) prox;
	return novoInimigo;
}

void moveInimigo(inimigo *elementos){

	for (inimigo *id = elementos; id != NULL; id = (inimigo*) id->prox ){
		id->x += 1;
	}
}

void inimigoAtira(inimigo *elementos){
	
	bala *tiro;

	for (inimigo *id = elementos; id != NULL; id = (inimigo*) id->prox ){
		tiro = tiroPistola(id->x - id->lado/2, id->y, id->face, id->arma);
	}
}

void destroiInimigo(inimigo *elemento){
	
	destroiPistola(elemento->arma);
	free(elemento);
}