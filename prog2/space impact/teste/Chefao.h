#ifndef __CHEFAO__
#define __CHEFAO__

#include "Jogador.h"
#include "Pistola.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define RAIO_F 180
#define CHACENCE_ATIRA_F 50


#define VELOCIDADE_INIMIGO 7

typedef struct chefao {
    unsigned short tipo, x, y;
    float angulo, velocidadeRotacao;
    unsigned char face, lado,  vida;
    ALLEGRO_BITMAP *sprite;
    pistola *arma;
} chefao;

chefao* criaChefao(int tipo, int x, int y);
void chefaoAtira(chefao *elemento, unsigned char trajetoria);
void atualizaBalasChefao(chefao *elemento);
unsigned char colisaoChefaoJogador(chefao *chefao, jogador *jogador);
void atualizaChefao(chefao *chefao, jogador *jogador);

#endif