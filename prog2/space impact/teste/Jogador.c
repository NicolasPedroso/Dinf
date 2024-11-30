#include <stdlib.h>
#include "Jogador.h"

jogador* criaJogador(unsigned char lado, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){

	if ((x - lado/2 < 0) || (x + lado/2 > max_x) || (y - lado/2 < 0) || (y + lado/2 > max_y)) return NULL;
	if (face > 3) return NULL;

	jogador *novoJogador = (jogador*) malloc(sizeof(jogador));
	if (!novoJogador) return NULL;
	novoJogador->lado = lado;
	novoJogador->face = face;
	novoJogador->vida = 5;
	novoJogador->x = x;
	novoJogador->y = y;
	novoJogador->controle = criaControle();
	novoJogador->arma = criaPistola();
	return novoJogador;
}

void moveJogador(jogador *elemento, char passos, unsigned char trajetoria, unsigned short max_x, unsigned short max_y){

	if (!trajetoria){ if ((elemento->x - passos*VELOCIDADE_JOGADOR) - elemento->lado/2 >= 0) elemento->x = elemento->x - passos*VELOCIDADE_JOGADOR;}
	else if (trajetoria == 1){ if ((elemento->x + passos*VELOCIDADE_JOGADOR) + elemento->lado/2 <= max_x) elemento->x = elemento->x + passos*VELOCIDADE_JOGADOR;}
	else if (trajetoria == 2){ if ((elemento->y - passos*VELOCIDADE_JOGADOR) - elemento->lado/2 >= 0) elemento->y = elemento->y - passos*VELOCIDADE_JOGADOR;}
	else if (trajetoria == 3){ if ((elemento->y + passos*VELOCIDADE_JOGADOR) + elemento->lado/2 <= max_y) elemento->y = elemento->y + passos*VELOCIDADE_JOGADOR;}
}

void jogadorAtira(jogador *elemento){
	bala *tiro;

	if (!elemento->face) tiro = tiroPistola(elemento->x - elemento->lado/2, elemento->y, elemento->face, elemento->arma);
	else if (elemento->face == 1) tiro = tiroPistola(elemento->x + elemento->lado/2, elemento->y, elemento->face, elemento->arma);
	if (tiro) elemento->arma->tiros = tiro;
}

void destroiJogador(jogador *elemento){
	
	destroiPistola(elemento->arma);
	destroiControle(elemento->controle);
	free(elemento);
}