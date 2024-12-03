#include "Inimigos.h"
#include <stdlib.h>

void defineCorInimigo(inimigo *id) {
    switch (id->tipo) {
        case 0:
            id->cor = al_map_rgb(255, 0, 0); /*Vermelho para cometas*/
            break;
        case 1:
            id->cor = al_map_rgb(0, 255, 0); /*Verde para o tipo 1*/
            break;
        case 2:
            id->cor = al_map_rgb(0, 0, 255); /*Azul para o tipo 2*/
            break;
        case 3:
            id->cor = al_map_rgb(255, 255, 0); /*Amarelo para o tipo 3*/
            break;
        default:
            id->cor = al_map_rgb(255, 255, 255); /*Branco para tipos desconhecidos*/
            break;
    }
}


inimigo* criaInimigo(int tipo, int x, int y) {
    inimigo* novoInimigo = (inimigo*)malloc(sizeof(inimigo));
    if (!novoInimigo) return NULL;

    novoInimigo->x = x;
    novoInimigo->y = y;
    novoInimigo->vida = 5*tipo;
    novoInimigo->lado = 7 + 7*tipo;
    novoInimigo->tipo = tipo;
    novoInimigo->prox = NULL;
    novoInimigo->arma = criaPistola();

    defineCorInimigo(novoInimigo);

    return novoInimigo;
}

void adicionaInimigo(inimigo **lista, int tipo, float x, float y) {
    inimigo* novo = criaInimigo(tipo, x, y);
    if (!novo) return;

    novo->prox = *lista;
    *lista = novo;
}

void inimigoAtira(inimigo *elemento){

    if (!elemento || !elemento->arma) return;

	bala *tiro;

    tiro = tiroPistola(elemento->x - elemento->lado/2, elemento->y, DIRECAO_ESQUERDA, elemento->arma);
    
	if (tiro) elemento->arma->tiros = tiro;
}

void balasInimigos(inimigo *inimigos) {
    
    for (inimigo *inimigo = inimigos; inimigo != NULL; inimigo = inimigo->prox) {
        if (inimigo->arma && inimigo->arma->tiros) {
            for (bala *id = inimigo->arma->tiros; id != NULL; id = (bala*) id->prox) {
                al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 165, 0)); /*Desenha cada bala*/
                moveBalas(inimigo->arma->tiros);
    	    }
	    }
    }
}

unsigned char colisaoInimigoJogador(inimigo *inimigo, jogador *jogador) {
    if (
        (
            ((jogador->y - jogador->lado / 2 >= inimigo->y - inimigo->lado / 2) &&
             (inimigo->y + inimigo->lado / 2 >= jogador->y - jogador->lado / 2)) ||
            ((inimigo->y - inimigo->lado / 2 >= jogador->y - jogador->lado / 2) &&
             (jogador->y + jogador->lado / 2 >= inimigo->y - inimigo->lado / 2))
        ) &&
        (
            ((jogador->x - jogador->lado / 2 >= inimigo->x - inimigo->lado / 2) &&
             (inimigo->x + inimigo->lado / 2 >= jogador->x - jogador->lado / 2)) ||
            ((inimigo->x - inimigo->lado / 2 >= jogador->x - jogador->lado / 2) &&
             (jogador->x + jogador->lado / 2 >= inimigo->x - inimigo->lado / 2))
        )
    ) {
        return 1; /*Ha colisao*/
    } else {
        return 0; /*Nao ha colisao*/
    }
}

void atualizaInimigos(inimigo *lista, jogador *jogador1) {
    for (inimigo *id = lista; id != NULL; id = id->prox) {
        switch (id->tipo) {
            case 0: /* Cometa */

                int dx = jogador1->x - id->x;
                int dy = jogador1->y - id->y;

                float variacao = (rand() % 20 - 10) / 100.0; /*Variacao entre -0.1 e 0.1*/

                if (abs(dx) > abs(dy)) {
                    if (dx > 0) {
                        id->x += VELOCIDADE_INIMIGO * (1 + variacao);
                    } else {
                        id->x -= VELOCIDADE_INIMIGO * (1 + variacao);
                    }
                } else {
                    if (dy > 0) {
                        id->y += VELOCIDADE_INIMIGO * (1 + variacao);
                    } else {
                        id->y -= VELOCIDADE_INIMIGO * (1 + variacao);
                    }
                }
            break;

            case 1: /*Scout*/
                id->x -= (2*VELOCIDADE_INIMIGO);

                if (rand() % 100 < 15) { 
                    inimigoAtira(id);
                }
            break;

            case 2: /*Soldier*/
                id->x -= (2*VELOCIDADE_INIMIGO);

                // Lógica de tiro (atirar com base em um tempo ou frequência)
                if (rand() % 100 < 25) { // Chance de 5% de atirar a cada atualização
                    inimigoAtira(id);
                }
            break;

            case 3: /*Heavy*/
                id->x -= (2*VELOCIDADE_INIMIGO);

                if (rand() % 100 < 30) {
                    inimigoAtira(id);
                }
            break;

            default:
                break;
        }
        
        if (colisaoInimigoJogador(id, jogador1)) {
            jogador1->vida -= 10; // Reduz a vida do jogador ao colidir
            id->vida = 0;        // Marca o inimigo como destruído
        }
    }
}

void desenhaInimigos(inimigo *lista) {
    for (inimigo *id = lista; id != NULL; id = id->prox) {
        al_draw_filled_rectangle(id->x-id->lado/2, id->y-id->lado/2, id->x+id->lado/2, id->y+id->lado/2, id->cor);
    }
}

void destroiInimigos(inimigo *lista) {
    while (lista) {
        inimigo *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}