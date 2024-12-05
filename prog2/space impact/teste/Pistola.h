#ifndef __PISTOLA__
#define __PISTOLA__

#include "Bala.h"

#define REGARGA_ESCOPETA 10
#define REGARGA_PISTOLA 1
#define REGARGA_METRALHADORA 5


typedef struct {
	unsigned char tempo;
	bala *tiros;	
} pistola;

pistola* criaPistola();
bala* tiroPistola(unsigned short x, unsigned short y, unsigned char trajetoria, pistola *arma);
void destroiPistola(pistola *elemento);

#endif