#ifndef __JOGADOR__
#define __JOGADOR__

#include "Controle.h"
#include "Pistola.h"

#define PASSO_JOGADOR 10

typedef struct {
	unsigned char lado;
	unsigned char face;
	unsigned char vida;
	unsigned short x;
	unsigned short y;
	controle *controle;
	pistola *arma;
} jogador;

jogador* criaJogador(unsigned char lado, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);
void moveJogador(jogador *elemento, char passos, unsigned char trajetoria, unsigned short max_x, unsigned short max_y);
void jogadorAtira(jogador *elemento);
void destroiJogador(jogador *elemento);

#endif