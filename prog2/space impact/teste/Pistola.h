#ifndef __PISTOLA__
#define __PISTOLA__

#include "Bala.h"

#define REGARGA_PISTOLA 10

typedef struct {
	unsigned char tempo;
	bala *tiros;	
} pistola;

pistola* criaPistola();
bala* tiroPistola(unsigned short x, unsigned short y, unsigned char trajetoria, pistola *arma);
void destroiPistola(pistola *elemento);

#endif