#ifndef __PISTOLA__ 																												//Guardas de inclusão
#define __PISTOLA__																												//Guardas de inclusão

#include "Bala.h"

#define REGARGA_PISTOLA 10																										//Tamanho, em frames, do tempo entre um tiro e outro

typedef struct {																												//Definição da estrutura de uma pistola
	unsigned char tempo;																										//Relógio de intervalo entre tiros
	bala *tiros;																												//Lista de balas ativas no campo disparadas pelas arma	
} pistola;																														//Definição do nome da estrutura

pistola* criaPistola();																										//Protótipo da função de criação de uma pistola
bala* tiroPistola(unsigned short x, unsigned short y, unsigned char trajetoria, pistola *arma);									//Protótipo da função de disparo de uma pistola
void destroiPistola(pistola *elemento);																							//Protótipo da função de destruição de uma pistola

#endif																															//Guardas de inclusão