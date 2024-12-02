#include <stdlib.h>
#include "Jogador.h"

jogador* criaJogador(unsigned char lado, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y){

	if ((x - lado/2 < 0) || (x + lado/2 > max_x) || (y - lado/2 < 0) || (y + lado/2 > max_y)) return NULL;
	if (face > 3) return NULL;

	jogador *novoJogador = (jogador*) malloc(sizeof(jogador));
	if (!novoJogador) return NULL;
	novoJogador->lado = lado;
	novoJogador->face = face;
	novoJogador->vida = 5;
	novoJogador->x = x;
	novoJogador->y = y;
	novoJogador->controle = criaControle();
	novoJogador->arma = criaPistola();
	return novoJogador;
}

void moveJogador(jogador *elemento, char passos, unsigned char trajetoria, unsigned short max_x, unsigned short max_y){

	if (!trajetoria){ if ((elemento->x - passos*VELOCIDADE_JOGADOR) - elemento->lado/2 >= 0) elemento->x = elemento->x - passos*VELOCIDADE_JOGADOR;}
	else if (trajetoria == 1){ if ((elemento->x + passos*VELOCIDADE_JOGADOR) + elemento->lado/2 <= max_x) elemento->x = elemento->x + passos*VELOCIDADE_JOGADOR;}
	else if (trajetoria == 2){ if ((elemento->y - passos*VELOCIDADE_JOGADOR) - elemento->lado/2 >= 0) elemento->y = elemento->y - passos*VELOCIDADE_JOGADOR;}
	else if (trajetoria == 3){ if ((elemento->y + passos*VELOCIDADE_JOGADOR) + elemento->lado/2 <= max_y) elemento->y = elemento->y + passos*VELOCIDADE_JOGADOR;}
}

unsigned char colisaoJogador(jogador *elemento_primeiro, jogador *elemento_segudo){

	if ((((elemento_segudo->y-elemento_segudo->lado/2 >= elemento_primeiro->y-elemento_primeiro->lado/2) && (elemento_primeiro->y+elemento_primeiro->lado/2 >= elemento_segudo->y-elemento_segudo->lado/2)) ||
		((elemento_primeiro->y-elemento_primeiro->lado/2 >= elemento_segudo->y-elemento_segudo->lado/2) && (elemento_segudo->y+elemento_segudo->lado/2 >= elemento_primeiro->y-elemento_primeiro->lado/2))) &&
		(((elemento_segudo->x-elemento_segudo->lado/2 >= elemento_primeiro->x-elemento_primeiro->lado/2) && (elemento_primeiro->x+elemento_primeiro->lado/2 >= elemento_segudo->x-elemento_segudo->lado/2)) ||
		((elemento_primeiro->x-elemento_primeiro->lado/2 >= elemento_segudo->x-elemento_segudo->lado/2) && (elemento_segudo->x+elemento_segudo->lado/2 >= elemento_primeiro->x-elemento_primeiro->lado/2)))) return 1;
	else return 0;
}

void jogadorAtira(jogador *elemento, unsigned char trajetoria){

	if (elemento == NULL) return;

	bala *tiro;

	switch (trajetoria) {
		case DIRECAO_ESQUERDA:
        	tiro = tiroPistola(elemento->x - elemento->lado/2, elemento->y, elemento->face, elemento->arma);
            break;
        case DIRECAO_DIREITA:
            tiro = tiroPistola(elemento->x + elemento->lado/2, elemento->y, elemento->face, elemento->arma);
			break;
        case DIRECAO_CIMA:
            tiro = tiroPistola(elemento->x, elemento->y - elemento->lado/2, elemento->face, elemento->arma);
            break;
        case DIRECAO_BAIXO:
            tiro = tiroPistola(elemento->x, elemento->y + elemento->lado/2, elemento->face, elemento->arma);
            break;
        default:
            break;
        }

	if (tiro) elemento->arma->tiros = tiro;
}

void destroiJogador(jogador *elemento){
	
	destroiPistola(elemento->arma);
	destroiControle(elemento->controle);
	free(elemento);
}