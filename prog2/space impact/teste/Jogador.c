#include <stdlib.h>
#include "Jogador.h"

#define X_TELA 800
#define Y_TELA 400

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

void atualizaPosicao(jogador *jogador1, jogador *jogador2){

	if (jogador1->controle->esquerda){
		moveJogador(jogador1, 1, DIRECAO_ESQUERDA, X_TELA, Y_TELA);
		jogador1->face = DIRECAO_ESQUERDA;
		if (colisaoJogador(jogador1, jogador2)) moveJogador(jogador1, -1, 0, X_TELA, Y_TELA);
	}
	if (jogador1->controle->direita){
		moveJogador(jogador1, 1, DIRECAO_DIREITA, X_TELA, Y_TELA);
		jogador1->face = DIRECAO_DIREITA;
		if (colisaoJogador(jogador1, jogador2)) moveJogador(jogador1, -1, 1, X_TELA, Y_TELA);
	}
	if (jogador1->controle->cima) {
		moveJogador(jogador1, 1, DIRECAO_CIMA, X_TELA, Y_TELA);
		jogador1->face = DIRECAO_CIMA;
		if (colisaoJogador(jogador1, jogador2)) moveJogador(jogador1, -1, 2, X_TELA, Y_TELA);
	}
	if (jogador1->controle->baixo){
		moveJogador(jogador1, 1, DIRECAO_BAIXO, X_TELA, Y_TELA);
		jogador1->face = DIRECAO_BAIXO;
		if (colisaoJogador(jogador1, jogador2)) moveJogador(jogador1, -1, 3, X_TELA, Y_TELA);
	}
	
	if (jogador2->controle->esquerda){
		moveJogador(jogador2, 1, DIRECAO_ESQUERDA, X_TELA, Y_TELA);
		jogador2->face = DIRECAO_ESQUERDA;
		if (colisaoJogador(jogador2, jogador1)) moveJogador(jogador2, -1, 0, X_TELA, Y_TELA);
	}
	if (jogador2->controle->direita){
		moveJogador(jogador2, 1, DIRECAO_DIREITA, X_TELA, Y_TELA);
		jogador2->face = DIRECAO_DIREITA;
		if (colisaoJogador(jogador2, jogador1)) moveJogador(jogador2, -1, 1, X_TELA, Y_TELA);
	}
	if (jogador2->controle->cima) {
		moveJogador(jogador2, 1, DIRECAO_CIMA, X_TELA, Y_TELA);
		jogador2->face = DIRECAO_CIMA;
		if (colisaoJogador(jogador2, jogador1)) moveJogador(jogador2, -1, 2, X_TELA, Y_TELA);
	}
	if (jogador2->controle->baixo){
		moveJogador(jogador2, 1, DIRECAO_BAIXO, X_TELA, Y_TELA);
		jogador2->face = DIRECAO_BAIXO;
		if (colisaoJogador(jogador2, jogador1)) moveJogador(jogador2, -1, 3, X_TELA, Y_TELA);
	}

	if (jogador1->controle->atira){
		if (!jogador1->arma->tempo){
			jogadorAtira(jogador1, jogador1->face);
			jogador1->arma->tempo = REGARGA_PISTOLA;
		} 
	}
	if (jogador2->controle->atira){
		if (!jogador2->arma->tempo){
			jogadorAtira(jogador2, jogador2->face);
			jogador2->arma->tempo = REGARGA_PISTOLA;
		}
	}
	moveBalas(jogador1->arma->tiros);
	moveBalas(jogador2->arma->tiros);
}

void atualizaBalas(jogador *jogador){
	
	bala *anterior = NULL;
	for (bala *id = jogador->arma->tiros; id != NULL;){
		if (!id->trajetoria) id->x -= MOVI_BALA;
		else if (id->trajetoria == 1) id->x += MOVI_BALA;
	
		
		if ((id->x < 0) || (id->x > X_TELA)){
			if (anterior){
				anterior->prox = id->prox;
				destroiBala(id);
				id = (bala*) anterior->prox;
			}
			else {
				jogador->arma->tiros = (bala*) id->prox;
				destroiBala(id);
				id = jogador->arma->tiros;
			}
		}
		else{
			anterior = id;
			id = (bala*) id->prox;
		}
	}
}

unsigned char veMortePVP(jogador *assassino, jogador *vitima){

	bala *anterior = NULL;
	for (bala *id = assassino->arma->tiros; id != NULL; id = (bala*) id->prox){
		if ((id->x >= vitima->x - vitima->lado/2) && (id->x <= vitima->x + vitima->lado/2) &&
		   (id->y >= vitima->y - vitima->lado/2) && (id->y <= vitima->y + vitima->lado/2)){
			vitima->vida--;
			if (vitima->vida){
				if (anterior){
					anterior->prox = id->prox;
					destroiBala(id);
					id = (bala*) anterior->prox;
				}
				else {
					assassino->arma->tiros = (bala*) id->prox;
					destroiBala(id);
					id = assassino->arma->tiros;
				}
				return 0;
			}
			else return 1;
		}
		anterior = id;
	}
	return 0;
}

void destroiJogador(jogador *elemento){
	
	destroiPistola(elemento->arma);
	destroiControle(elemento->controle);
	free(elemento);
}