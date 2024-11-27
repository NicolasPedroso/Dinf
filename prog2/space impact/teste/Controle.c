#include <stdlib.h>
#include "Controle.h"

controle* criaControle(){

	controle *elemento = (controle*) malloc (sizeof(controle));
	if (!elemento) return NULL;
	elemento->direita = 0;
	elemento->esquerda = 0;
	elemento->cima = 0;
	elemento->baixo = 0;
	elemento->atira = 0;
	return elemento;
}

void destroiControle(controle *elemento){ free(elemento);}

void controleEsquerda(controle *elemento){ elemento->esquerda = elemento->esquerda ^ 1;}

void controleDireita(controle *elemento){ elemento->direita = elemento->direita ^ 1;}

void controleCima(controle *elemento){ elemento->cima = elemento->cima ^ 1;}

void controleBaixo(controle *elemento){ elemento->baixo = elemento->baixo ^ 1;}

void controleAtira(controle *elemento){ elemento->atira = elemento->atira ^ 1;}