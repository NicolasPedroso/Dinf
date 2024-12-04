#ifndef __BALA__
#define __BALA__

#define DIRECAO_ESQUERDA 0
#define DIRECAO_DIREITA 1
#define DIRECAO_CIMA 2
#define DIRECAO_BAIXO 3
#define DIRECAO_ESQUERDA_CIMA 4
#define DIRECAO_DIREITA_CIMA 5
#define DIRECAO_ESQUERDA_BAIXO 6
#define DIRECAO_DIREITA_BAIXO 7

#define MOVI_BALA 7

/*Tela que todas as outras vao usar*/
#define X_TELA 800
#define Y_TELA 400


typedef struct {
	unsigned short x;
	unsigned short y;
	unsigned char trajetoria;
	struct bala *prox;
} bala;

bala* criaBala(unsigned short x, unsigned short y, unsigned char trajetoria, bala *prox);
void moveBalas(bala *elementos);
void destroiBala(bala *elemento);

#endif