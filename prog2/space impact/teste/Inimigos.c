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
    novoInimigo->vida = 5 + 5*tipo;
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

void destroiInimigo(inimigo *elemento){

	free(elemento);
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
    
    if ((((jogador->y-jogador->lado/2 >= inimigo->y-inimigo->lado/2) && (inimigo->y+inimigo->lado/2 >= jogador->y-jogador->lado/2)) ||
		((inimigo->y-inimigo->lado/2 >= jogador->y-jogador->lado/2) && (jogador->y+jogador->lado/2 >= inimigo->y-inimigo->lado/2))) &&
		(((jogador->x-jogador->lado/2 >= inimigo->x-inimigo->lado/2) && (inimigo->x+inimigo->lado/2 >= jogador->x-jogador->lado/2)) ||
		((inimigo->x-inimigo->lado/2 >= jogador->x-jogador->lado/2) && (jogador->x+jogador->lado/2 >= inimigo->x-inimigo->lado/2)))) return 1;
	else return 0;
}

void atualizaInimigos(inimigo **lista, jogador *jogador) {
    inimigo *anterior = NULL;
    inimigo *atual = *lista;

    while (atual != NULL) {
        switch (atual->tipo) {
            case 0: /* Cometa */
                int dx = jogador->x - atual->x;
                int dy = jogador->y - atual->y;

                float variacao = (rand() % 20 - 10) / 100.0; /* Variação entre -0.1 e 0.1 */

                if (abs(dx) > abs(dy)) {
                    if (dx > 0) {
                        atual->x += VELOCIDADE_INIMIGO * (1 + variacao);
                        if (colisaoInimigoJogador(atual, jogador)) {
                            jogador->vida -= 1;
                        }
                    } else {
                        atual->x -= VELOCIDADE_INIMIGO * (1 + variacao);
                    }
                } else {
                    if (dy > 0) {
                        atual->y += VELOCIDADE_INIMIGO * (1 + variacao);
                    } else {
                        atual->y -= VELOCIDADE_INIMIGO * (1 + variacao);
                    }
                }
                break;

            case 1: /* Scout */
                atual->x -= (atual->tipo * VELOCIDADE_INIMIGO);
                break;
            case 2: /* Soldier */
                atual->x -= (atual->tipo * VELOCIDADE_INIMIGO);
                break;
            case 3: /* Heavy */
                atual->x -= (atual->tipo * VELOCIDADE_INIMIGO);

                int chanceDeAtirar = (atual->tipo == 1) ? 15 : (atual->tipo == 2) ? 25 : 30;
                if (rand() % 100 < chanceDeAtirar) {
                    inimigoAtira(atual);
                }
                break;

            default:
                break;
        }

        if (colisaoInimigoJogador(atual, jogador)) {
            jogador->vida -= 1;
            atual->vida = 0;
        }
        
        if (atual->x - atual->lado / 2 < 0 && atual->tipo != 0) {
            atual->vida = 0;
        }

        if (atual->vida <= 0) {
            inimigo *temp = atual;
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                *lista = atual->prox;  // Atualiza a cabeça da lista
            }
            destroiPistola(temp->arma);
            free(temp);
            atual = (anterior) ? anterior->prox : *lista;
        } else {
            anterior = atual;
            atual = atual->prox;
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