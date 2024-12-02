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
    novoInimigo->lado = 7*tipo;
    novoInimigo->tipo = tipo;
    novoInimigo->prox = NULL;

    defineCorInimigo(novoInimigo);

    return novoInimigo;
}

void adicionaInimigo(inimigo **lista, int tipo, float x, float y) {
    inimigo* novo = criaInimigo(tipo, x, y);
    if (!novo) return;

    novo->prox = *lista;
    *lista = novo;
}

void atualizaInimigos(inimigo *lista, jogador *jogador1, jogador *jogador2) {
    for (inimigo *id = lista; id != NULL; id = id->prox) {
        switch (id->tipo) {
            case 0: /* Cometa */
                // Cálculo da diferença de posição em relação ao jogador
                int dx = jogador1->x - id->x;
                int dy = jogador1->y - id->y;

                // Calcular a direção desejada, mas com uma pequena variação para imprecisão
                float variacao = (rand() % 20 - 10) / 100.0; // Variação aleatória entre -0.1 e 0.1

                // Ajustar a posição do cometa
                if (abs(dx) > abs(dy)) { // Movimento horizontal predominante
                    if (dx > 0) {
                        id->x += VELOCIDADE_INIMIGO * (1 + variacao);
                    } else {
                        id->x -= VELOCIDADE_INIMIGO * (1 + variacao);
                    }
                } else { // Movimento vertical predominante
                    if (dy > 0) {
                        id->y += VELOCIDADE_INIMIGO * (1 + variacao);
                    } else {
                        id->y -= VELOCIDADE_INIMIGO * (1 + variacao);
                    }
                }
            break;

            case 1: /*Scout*/
                id->x -= (2*VELOCIDADE_INIMIGO);

                // Lógica de tiro (atirar com base em um tempo ou frequência)
                if (rand() % 100 < 5) { // Chance de 5% de atirar a cada atualização
                    // Chame a função de disparo da arma do inimigo aqui
                    //atiraInimigo(id);
                }
            break;

            case 2: /* Mais um tipo de inimigo */
                id->x -= (2*VELOCIDADE_INIMIGO);

                // Lógica de tiro (atirar com base em um tempo ou frequência)
                if (rand() % 100 < 5) { // Chance de 5% de atirar a cada atualização
                    // Chame a função de disparo da arma do inimigo aqui
                    //atiraInimigo(id);
                }
            break;

            case 3: /* Outro tipo adicional de inimigo */
                id->x -= (2*VELOCIDADE_INIMIGO);

                // Lógica de tiro (atirar com base em um tempo ou frequência)
                if (rand() % 100 < 5) { // Chance de 5% de atirar a cada atualização
                    // Chame a função de disparo da arma do inimigo aqui
                    //atiraInimigo(id);
                }
            break;

            default:
                // Lógica padrão, se necessário, quando o tipo não for reconhecido
                break;
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