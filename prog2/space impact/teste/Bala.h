#ifndef __BALA__
#define __BALA__

#define MOVI_BALA 5

typedef struct {
	unsigned short x;
	unsigned short y;
	unsigned char trajetoria;
	struct bala *prox;
} bala;

bala* criaBala(unsigned short x, unsigned short y, unsigned char trajetoria, bala *prox);
void moveBala(bala *elementos);
void destroiBala(bala *elemento);

#endif