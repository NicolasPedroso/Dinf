#include "BackGround.h"

void iniciaBackground(background *fundo, int x, int y, float velocidadeX, float velocidadeY, int largura, int altura, ALLEGRO_BITMAP *imagem) {
    
    fundo->x = x;
    fundo->y = y;
    fundo->velocidadeX = velocidadeX;
    fundo->velocidadeY = velocidadeY;
    fundo->largura = largura;
    fundo->altura = altura;
    fundo->imagem = imagem;
}

void atualizaBackground(background *fundo) {
    
    fundo->x += fundo->velocidadeX;
    if (fundo->x + fundo->largura <= 0) fundo->x = 0;
}

void desenhaBackground(background *fundo) {
    al_draw_bitmap(fundo->imagem, fundo->x, fundo->y, 0);

    if (fundo->x + fundo->largura < 800) al_draw_bitmap(fundo->imagem, fundo->x, fundo->y, 0);
}