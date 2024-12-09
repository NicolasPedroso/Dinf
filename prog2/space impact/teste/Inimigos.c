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
    novoInimigo->vida = 1 + 1*tipo;
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

void destroiInimigo(inimigo *elemento) {

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

unsigned char veBalasJogador(jogador *assassino, inimigo *vitima) {
    bala *anterior = NULL;
    for (bala *id = assassino->arma->tiros; id != NULL; id = (bala*) id->prox) {
        if ((id->x >= vitima->x - vitima->lado/2) && (id->x <= vitima->x + vitima->lado/2) &&
            (id->y >= vitima->y - vitima->lado/2) && (id->y <= vitima->y + vitima->lado/2)) {
            vitima->vida--;
            assassino->pontos += 100;
            if (vitima->vida <= 0) {
                return 1;
            }
            
            if (anterior) {
                anterior->prox = id->prox;
                destroiBala(id);
                id = (bala*) anterior->prox;
            } else {
                assassino->arma->tiros = (bala*) id->prox;
                destroiBala(id);
                id = assassino->arma->tiros;
            }
            return 0;
        }
        anterior = id;
    }
    return 0;
}

unsigned char veBalasInimigo(inimigo *assassino, jogador *vitima) {
    bala *anterior = NULL;
    for (bala *id = assassino->arma->tiros; id != NULL; id = (bala*) id->prox) {
        if ((id->x >= vitima->x - vitima->lado/2) && (id->x <= vitima->x + vitima->lado/2) &&
            (id->y >= vitima->y - vitima->lado/2) && (id->y <= vitima->y + vitima->lado/2)) {
            vitima->vida--;
            if (vitima->vida <= 0) {
                return 1;
            }
            
            if (anterior) {
                anterior->prox = id->prox;
                destroiBala(id);
                id = (bala*) anterior->prox;
            } else {
                assassino->arma->tiros = (bala*) id->prox;
                destroiBala(id);
                id = assassino->arma->tiros;
            }
            return 0;
        }
        anterior = id;
    }
    return 0;
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
                        atual->x += (VELOCIDADE_INIMIGO - atual->tipo - 1) * (1 + variacao);
                        if (colisaoInimigoJogador(atual, jogador)) {
                            jogador->vida -= 1;
                        }
                    } else {
                        atual->x -= (VELOCIDADE_INIMIGO - atual->tipo - 1) * (1 + variacao);
                    }
                } else {
                    if (dy > 0) {
                        atual->y += (VELOCIDADE_INIMIGO - atual->tipo - 1) * (1 + variacao);
                    } else {
                        atual->y -= (VELOCIDADE_INIMIGO - atual->tipo - 1) * (1 + variacao);
                    }
                }
                break;

            case 1: /* Scout */
                atual->x -= (VELOCIDADE_INIMIGO -atual->tipo);
                break;
            case 2: /* Soldier */
                atual->x -= (VELOCIDADE_INIMIGO -atual->tipo);
                break;
            case 3: /* Heavy */
                atual->x -= (VELOCIDADE_INIMIGO -atual->tipo);
                break;

            default:
                break;
        }

        int chanceDeAtirar = (atual->tipo == 2) ? 1.5 : (atual->tipo == 3) ? 2.5 : 3.0;
        if (rand() % 100 < chanceDeAtirar && atual->tipo != 0) {
            inimigoAtira(atual);
        }

        if (colisaoInimigoJogador(atual, jogador)) {
            jogador->vida -= 1;
            atual->vida = 0;
        }
        veBalasJogador(jogador, atual);

        veBalasInimigo(atual, jogador);

        
        if (atual->x - atual->lado / 2 < 0 && atual->tipo != 0) {
            atual->vida = 0;
        }

        if (atual->vida <= 0) {
            inimigo *temp = atual;
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                *lista = atual->prox;  /*Atualiza a cabeca da lista*/
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

    ALLEGRO_BITMAP *missel = al_load_bitmap("acessorios/missel.png");
    ALLEGRO_BITMAP *inimigoScout = al_load_bitmap("acessorios/inimigo_scout.png");
    ALLEGRO_BITMAP *inimigoSoldier = al_load_bitmap("acessorios/inimigo_soldier.png");
    ALLEGRO_BITMAP *inimigoHeavy = al_load_bitmap("acessorios/inimigo_heavy.png");
    

    for (inimigo *id = lista; id != NULL; id = id->prox) {
        //al_draw_filled_rectangle(id->x-id->lado/2, id->y-id->lado/2, id->x+id->lado/2, id->y+id->lado/2, id->cor);
        if (id->tipo == 0)al_draw_bitmap(missel, id->x - 5, id->y - 5, 0);
        if (id->tipo == 1)al_draw_bitmap(inimigoScout, id->x - 33, id->y - 32, 0);
        if (id->tipo == 2)al_draw_bitmap(inimigoSoldier, id->x - 32, id->y - 32, 0);
        if (id->tipo == 3)al_draw_bitmap(inimigoHeavy, id->x - 28, id->y - 32, 0);
    }

    al_destroy_bitmap(missel);
    al_destroy_bitmap(inimigoScout);
    al_destroy_bitmap(inimigoSoldier);
    al_destroy_bitmap(inimigoHeavy);
}

void destroiInimigos(inimigo *lista) {
    while (lista) {
        inimigo *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}