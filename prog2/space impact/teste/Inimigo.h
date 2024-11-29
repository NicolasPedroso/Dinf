#ifndef __JOGADOR__
#define __JOGADOR__

#include "Pistola.h"

#define PASSO_INIMIGO 12

typedef struct inimigo inimigo;

struct inimigo {
    unsigned char lado;
    unsigned char face;
    unsigned char vida;
    unsigned short x;
    unsigned short y;
    pistola *arma;
    inimigo *prox;
};

inimigo* criaInimigo(unsigned char lado, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y, inimigo *prox);
void moveInimigo(inimigo *elementos);
void inimigoAtira(inimigo *elementos);
void destroiInimigo(inimigo *elemento);

#endif