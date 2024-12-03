#ifndef __JOGADOR__
#define __JOGADOR__

#include "Controle.h"
#include "Pistola.h"

#define VELOCIDADE_JOGADOR 7	

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
unsigned char colisaoJogador(jogador *elemento_primeiro, jogador *elemento_segudo);
void jogadorAtira(jogador *elemento, unsigned char trajetoria);
void atualizaPosicao(jogador *jogador1, jogador *jogador2);
void atualizaBalas(jogador *jogador);
unsigned char veMortePVP(jogador *assassino, jogador *vitima);
void destroiJogador(jogador *elemento);

#endif