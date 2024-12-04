#ifndef __CHEFAO__
#define __CHEFAO__

#include "Jogador.h"
#include "Pistola.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


#define VELOCIDADE_ROTACAO 0.1

typedef struct chefao {
    unsigned short x;
	unsigned short y;
    unsigned char face;
    unsigned char lado;
    unsigned char vida;
    pistola *arma;
} chefao;


chefao* criaChefao1(int x, int y, unsigned char face);
chefao* criaChefao2(int x, int y);
void chefaoAtira(chefao *elemento);
void balasChefao(chefao *elemento);
unsigned char colisaoInimigoJogador(chefao *elemento, jogador *jogador);
void atualizaChefao(chefao *elemento, jogador *jogador1);
void desenhaChefao(chefao *elemento);
void destroiChefao(chefao *elemento);

#endif