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
    novoChefao->vida = 150;
    novoChefao->lado = 50;
    novoChefao->angulo = 0;
    novoChefao->velocidadeRotacao = 0.07;
    novoChefao->arma = criaPistola();

    return novoChefao;
}

void destroiChefao(chefao *elemento) {
    if (!elemento) return;
    destroiPistola(elemento->arma);
    free(elemento);
}

void chefaoAtira(chefao *elemento, unsigned char trajetoria) {
    if (!elemento || !elemento->arma) return;

    bala *tiro = tiroPistola(elemento->x - elemento->lado / 2, elemento->y, trajetoria, elemento->arma);
    if (tiro) elemento->arma->tiros = tiro;
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

        al_draw_filled_rectangle(chefao->x - chefao->lado, chefao->y - chefao->lado / 2, chefao->x + chefao->lado / 2,chefao->y + chefao->lado / 2, al_map_rgb(255, 0, 0));
    	al_draw_bitmap(chefe1, chefao->x - 70, chefao->y - 64, 0);

        al_destroy_bitmap(chefe1);

    } else if (chefao->tipo == 1){
        ALLEGRO_BITMAP *chefe2 = al_load_bitmap("acessorios/chefe_2.png");

        if(!chefe2) {
            fprintf(stderr, "Erro ao carregar o bitmap do chefe (Fase 2).\n");
            return;
        }

        // Atualiza a posição do chefe rotacionando ao redor do jogador
        chefao->x = jogador->x + RAIO_F * cos(chefao->angulo);
        chefao->y = jogador->y + RAIO_F * sin(chefao->angulo);

        // Desenha o chefe rotacionado
        al_draw_rotated_bitmap(
            chefe2,
            al_get_bitmap_width(chefe2) / 2.0,
            al_get_bitmap_height(chefe2) / 2.0,
            chefao->x, chefao->y,
            chefao->angulo, 0
        );

        // Atualiza o ângulo para o próximo quadro
        chefao->angulo += chefao->velocidadeRotacao;
        if (chefao->angulo >= 2 * M_PI) {
            chefao->angulo -= 2 * M_PI; // Mantém o ângulo no intervalo [0, 2*PI]
        }

        al_destroy_bitmap(chefe2);
    } else {
        fprintf(stderr, "Sem Chefe para ser desenhado\n");
    }
}


void atualizaChefao(chefao *chefao, jogador *jogador) {
    if (!chefao) return;

    switch (chefao->tipo) {
        case 0:  /*Chefe1*/
            chefao->y = jogador->y;
            if(chefao->arma->tempo) {
                chefaoAtira(chefao, DIRECAO_ESQUERDA);
                chefaoAtira(chefao, DIRECAO_ESQUERDA_CIMA);
                chefaoAtira(chefao, DIRECAO_ESQUERDA_BAIXO);
            } else {
                chefao->arma->tempo--;
            }

            if (colisaoChefaoJogador(chefao, jogador)) {
                jogador->vida -= 1;
                chefao->vida -= 5;
            }

            chefeVeBalasJogador(jogador, chefao);

            jogadorVeBalasChefe(chefao,jogador);

            desenhaChefao(chefao, jogador);


            break;


        case 1:

            break;

        default:
            break;
    }
    if (chefao->vida <= 0) {
        destroiChefao(chefao);
    }
}