#ifndef __INIMIGOS__
#define __INIMIGOS__

#include "Jogador.h"
#include "Pistola.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


#define MAX_INIMIGOS 10
#define VELOCIDADE_INIMIGO 7

typedef struct inimigo {
    unsigned short x;
	unsigned short y;
    unsigned char lado;
    unsigned short tipo;
    unsigned char vida;
    pistola *arma;
    struct inimigo *prox;
    ALLEGRO_COLOR cor;
} inimigo;

void defineCorInimigo(inimigo *id);
inimigo* criaInimigo(int tipo, int x, int y);
void adicionaInimigo(inimigo **lista, int tipo, float x, float y);
void destroiInimigo(inimigo *elemento);
void inimigoAtira(inimigo *elemento);
void balasInimigos(inimigo *inimigos);
unsigned char colisaoInimigoJogador(inimigo *inimigo, jogador *jogador);
void limiteInimigos(inimigo **inimigo);
void atualizaInimigos(inimigo **lista, jogador *jogador);
void desenhaInimigos(inimigo *lista);
void destroiInimigos(inimigo *lista);

#endif