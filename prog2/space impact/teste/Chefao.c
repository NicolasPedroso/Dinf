#include "Chefao.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



chefao* criaChefao(int tipo, int x, int y) {
    chefao* novoChefao = (chefao*)malloc(sizeof(chefao));
    if (!novoChefao) return NULL;

    novoChefao->tipo = tipo;
    novoChefao->x = x;
    novoChefao->y = y;
    novoChefao->face = 0;
    novoChefao->vida = 1/*25*/;
    novoChefao->lado = 50;
    novoChefao->angulo = 0;
    novoChefao->velocidadeRotacao = 0.07;
    novoChefao->arma = criaPistola();

    return novoChefao;
}

void chefaoAtira(chefao *elemento, unsigned char trajetoria) {
    if (!elemento || !elemento->arma) return;

    bala *tiro = tiroPistola(elemento->x - elemento->lado / 2, elemento->y, trajetoria, elemento->arma);
    if (tiro) elemento->arma->tiros = tiro;
}

void balasChefao(chefao *chefao) {
    
    if (chefao->arma && chefao->arma->tiros) {
        for (bala *id = chefao->arma->tiros; id != NULL; id = (bala*) id->prox) {
            al_draw_filled_circle(id->x, id->y, 2, al_map_rgb(255, 165, 0)); /*Desenha cada bala*/
            moveBalas(chefao->arma->tiros);
        }
	}
}

unsigned char chefeVeBalasJogador(jogador *assassino, chefao *vitima) {
   
    bala *anterior = NULL;
    for (bala *id = assassino->arma->tiros; id != NULL; id = (bala*) id->prox) {
        if ((id->x >= vitima->x - vitima->lado / 2) && (id->x <= vitima->x + vitima->lado / 2) &&
            (id->y >= vitima->y - vitima->lado / 2) && (id->y <= vitima->y + vitima->lado / 2)) {
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

unsigned char jogadorVeBalasChefe(chefao *assassino, jogador *vitima) {
    
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


unsigned char colisaoChefaoJogador(chefao *chefao, jogador *jogador) {
    return (((jogador->y - jogador->lado / 2 >= chefao->y - chefao->lado / 2) &&
             (chefao->y + chefao->lado / 2 >= jogador->y - jogador->lado / 2)) ||
            ((chefao->y - chefao->lado / 2 >= jogador->y - jogador->lado / 2) &&
             (jogador->y + jogador->lado / 2 >= chefao->y - chefao->lado / 2))) &&
           (((jogador->x - jogador->lado / 2 >= chefao->x - chefao->lado / 2) &&
             (chefao->x + chefao->lado / 2 >= jogador->x - jogador->lado / 2)) ||
            ((chefao->x - chefao->lado / 2 >= jogador->x - jogador->lado / 2) &&
             (jogador->x + jogador->lado / 2 >= chefao->x - chefao->lado / 2)));
}

void desenhaChefao(chefao *chefao, jogador *jogador) {
    if (!chefao) return;

    if (chefao->tipo == 0) {
        
        ALLEGRO_BITMAP *chefe1 = al_load_bitmap("acessorios/chefe_1.png");

        if(!chefe1) {
            fprintf(stderr, "Erro ao carregar o bitmap do chefe (Fase 1).\n");
            return;
        }

        //al_draw_filled_rectangle(chefao->x - chefao->lado, chefao->y - chefao->lado / 2, chefao->x + chefao->lado / 2,chefao->y + chefao->lado / 2, al_map_rgb(255, 0, 0));
    	al_draw_bitmap(chefe1, chefao->x - 70, chefao->y - 64, 0);

        al_destroy_bitmap(chefe1);

    } else if (chefao->tipo == 1){
        
        ALLEGRO_BITMAP *chefe2 = al_load_bitmap("acessorios/chefe_2.png");

        if(!chefe2) {
            fprintf(stderr, "Erro ao carregar o bitmap do chefe (Fase 2).\n");
            return;
        }

        chefao->x = jogador->x + RAIO_F * cos(chefao->angulo);
        chefao->y = jogador->y + RAIO_F * sin(chefao->angulo);

        /*Desenha o chefe rotacionado*/
        //l_draw_filled_rectangle(chefao->x - chefao->lado, chefao->y - chefao->lado / 2, chefao->x + chefao->lado / 2,chefao->y + chefao->lado / 2, al_map_rgb(255, 0, 0));
    	al_draw_rotated_bitmap(
            chefe2,
            al_get_bitmap_width(chefe2) / 2.0,
            al_get_bitmap_height(chefe2) / 2.0,
            chefao->x, chefao->y,
            chefao->angulo, 0
        );

        /*Atualiza ângulo*/
        chefao->angulo += chefao->velocidadeRotacao;
        if (chefao->angulo >= 2 * M_PI) {
            chefao->angulo -= 2 * M_PI;
        }

        al_destroy_bitmap(chefe2);
    }
}


void atualizaChefao(chefao *chefao, jogador *jogador) {
    if (!chefao) return;


    switch (chefao->tipo) {
        case 0:  /*Chefe1*/

            int dy = jogador->y - chefao->y;
            float variacao = (rand() % 20 - 10) / 100.0;
            chefao->y = jogador->y + VELOCIDADE_JOGADOR * (1 + variacao);

            if(chefao->vida <= 0) {
                chefao->x = 1000;
                chefao->y = 1000; 
            } else if (rand() % 100 < CHACENCE_ATIRA_F) {
                if (rand() %100 < 15 ) {
                    if (!chefao->arma->tempo) {
                        chefaoAtira(chefao, DIRECAO_ESQUERDA);
                        chefaoAtira(chefao, DIRECAO_ESQUERDA_CIMA);
                        chefaoAtira(chefao, DIRECAO_ESQUERDA_BAIXO);
                        chefao->arma->tempo = REGARGA_ESCOPETA;
                    } else {
                        chefao->arma->tempo--;
                    }
                } else {
                    if (!chefao->arma->tempo) {
                        chefaoAtira(chefao, DIRECAO_ESQUERDA);
                        chefao->arma->tempo = REGARGA_PISTOLA;
                    } else {
                        chefao->arma->tempo--;
                    }
                }            
            }

            if (colisaoChefaoJogador(chefao, jogador)) {
                jogador->vida -= 1;
                chefao->vida -= 5;
            }

            chefeVeBalasJogador(jogador, chefao); /*jogador atira chefe*/

            jogadorVeBalasChefe(chefao,jogador);/*chefe atira jogador*/

            desenhaChefao(chefao, jogador);

            break;


        case 1:
            if (chefao->vida <= 0) {
                chefao->x = 1000;
                chefao->y = 1000; 
            } else {
                
                chefeVeBalasJogador(jogador, chefao); /*jogador atira chefe*/
                jogadorVeBalasChefe(chefao, jogador); /*chefe atira jogador*/

                desenhaChefao(chefao, jogador);

                if (chefao->x == jogador->x + RAIO_F || chefao->x == jogador->x - RAIO_F || 
                    chefao->y == jogador->y + RAIO_F || chefao->y == jogador->y - RAIO_F) {

                    if (chefao->x == jogador->x - RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_DIREITA);
                        chefaoAtira(chefao, DIRECAO_DIREITA_CIMA);
                        chefaoAtira(chefao, DIRECAO_DIREITA_BAIXO);
                    } else if (chefao->x == jogador->x + RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_ESQUERDA);
                        chefaoAtira(chefao, DIRECAO_ESQUERDA_CIMA);
                        chefaoAtira(chefao, DIRECAO_ESQUERDA_BAIXO);
                    } else if (chefao->y == jogador->y - RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_BAIXO);
                        chefaoAtira(chefao, DIRECAO_DIREITA_BAIXO);
                        chefaoAtira(chefao, DIRECAO_ESQUERDA_BAIXO);
                    } else if (chefao->y == jogador->y + RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_CIMA);
                        chefaoAtira(chefao, DIRECAO_ESQUERDA_CIMA);
                        chefaoAtira(chefao, DIRECAO_DIREITA_CIMA);
                    }
                } else {
                    if (chefao->x == jogador->x - RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_DIREITA);
                    } else if (chefao->x == jogador->x + RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_ESQUERDA);
                    } else if (chefao->y == jogador->y - RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_BAIXO);
                    } else if (chefao->y == jogador->y + RAIO_F) {
                        chefaoAtira(chefao, DIRECAO_CIMA);
                    }
                }
                if (colisaoChefaoJogador(chefao, jogador)) {
                    jogador->vida -= 1;
                    chefao->vida -= 5;
                }
            }
            break;


        default:
            break;
    }

    balasChefao(chefao);
}