#ifndef __CHEFAO__
#define __CHEFAO__

#include <allegro5/allegro5.h>

typedef struct background{
    unsigned short x;
	unsigned short y;
    float velocidadeX;
    float velocidadeY;

    int largura;
    int altura;

    ALLEGRO_BITMAP *imagem;

} background;

void iniciaBackground(background *fundo, int x, int y, float velocidadeX, float velocidadey, int largura, int altura, ALLEGRO_BITMAP *imagem);
void atualizaBackground(background *fundo);
void desenhaBackground(background *fundo);
void mudaEstado(int *estado, int novoEstado);

#endif