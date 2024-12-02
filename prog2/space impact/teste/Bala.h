#ifndef __BALA__
#define __BALA__

#define DIRECAO_ESQUERDA 0
#define DIRECAO_DIREITA 1
#define DIRECAO_CIMA 2
#define DIRECAO_BAIXO 3
#define MOVI_BALA 7

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