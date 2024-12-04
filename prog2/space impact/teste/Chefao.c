#include <stdlib.h>
#include "Chefao.h"

chefao* criaChefao1(int x, int y, unsigned char face){
    
    chefao* novoChefao = (chefao*)malloc(sizeof(chefao));
    if (!novoChefao) return NULL;

    novoChefao->x = x;
    novoChefao->y = y;
    novoChefao->face = face;
    novoChefao->vida = 150;
    novoChefao->lado = 50;
    novoChefao->arma = criaPistola();

    return novoChefao;
}

chefao* criaChefao2(int x, int y) {

    chefao* novoChefao = (chefao*)malloc(sizeof(chefao));
    if (!novoChefao) return NULL;

    novoChefao->x = x;
    novoChefao->y = y;
    novoChefao->vida = 150;
    novoChefao->lado = 50;
    novoChefao->arma = criaPistola();

    return novoChefao;
}
void chefaoAtira1(chefao *elemento) {

    if (!elemento || !elemento->arma) return;

	bala *tiro;
    
    switch (elemento->face) {
            case DIRECAO_ESQUERDA:
                tiro = tiroPistola(elemento->x - elemento->lado/2, elemento->y, DIRECAO_ESQUERDA, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->x - elemento->lado/2, elemento->y, DIRECAO_ESQUERDA_BAIXO, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->x - elemento->lado/2, elemento->y, DIRECAO_ESQUERDA_CIMA, elemento->arma);
                if (tiro) elemento->arma->tiros = tiro;
                break;
            case DIRECAO_DIREITA:
                tiro = tiroPistola(elemento->x + elemento->lado/2, elemento->y, DIRECAO_DIREITA, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->x + elemento->lado/2, elemento->y, DIRECAO_DIREITA_BAIXO, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->x + elemento->lado/2, elemento->y, DIRECAO_DIREITA_CIMA, elemento->arma);
                if (tiro) elemento->arma->tiros = tiro;
                break;
            case DIRECAO_CIMA:
                tiro = tiroPistola(elemento->y - elemento->lado/2, elemento->y, DIRECAO_CIMA, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->y - elemento->lado/2, elemento->y, DIRECAO_DIREITA_CIMA, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->y - elemento->lado/2, elemento->y, DIRECAO_ESQUERDA_CIMA, elemento->arma);
                if (tiro) elemento->arma->tiros = tiro;
                break;
            case DIRECAO_BAIXO:
                tiro = tiroPistola(elemento->y + elemento->lado/2, elemento->y, DIRECAO_BAIXO, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->y + elemento->lado/2, elemento->y, DIRECAO_DIREITA_BAIXO, elemento->arma);
	            if (tiro) elemento->arma->tiros = tiro;
                tiro = tiroPistola(elemento->y + elemento->lado/2, elemento->y, DIRECAO_ESQUERDA_BAIXO, elemento->arma);
                if (tiro) elemento->arma->tiros = tiro;
                break;
            default:
                break;
        }
}

void chefaoAtira2(chefao *elemento) {

}


void balasChefao(chefao *elemento) {

	bala *anterior = NULL;
	for (bala *id = elemento->arma->tiros; id != NULL;){
		if (!id->trajetoria) id->x -= MOVI_BALA;
		else if (id->trajetoria == 1) id->x += MOVI_BALA;
	
		
		if ((id->x < 0) || (id->x > X_TELA)){
			if (anterior){
				anterior->prox = id->prox;
				destroiBala(id);
				id = (bala*) anterior->prox;
			}
			else {
				elemento->arma->tiros = (bala*) id->prox;
				destroiBala(id);
				id = elemento->arma->tiros;
			}
		}
		else if((id->y < 0) || (id->y > Y_TELA)){
			if (anterior){
				anterior->prox = id->prox;
				destroiBala(id);
				id = (bala*) anterior->prox;
			}
			else {
				elemento->arma->tiros = (bala*) id->prox;
				destroiBala(id);
				id = elemento->arma->tiros;
			}
		}
		else {
			anterior = id;
			id = (bala*) id->prox;
		}
	}
}

unsigned char colisaoChefaoJogador(chefao *elemento, jogador *jogador){
    
    if ((((jogador->y-jogador->lado/2 >= elemento->y-elemento->lado/2) && (elemento->y+elemento->lado/2 >= jogador->y-jogador->lado/2)) ||
		((elemento->y-elemento->lado/2 >= jogador->y-jogador->lado/2) && (jogador->y+jogador->lado/2 >= elemento->y-elemento->lado/2))) &&
		(((jogador->x-jogador->lado/2 >= elemento->x-elemento->lado/2) && (elemento->x+elemento->lado/2 >= jogador->x-jogador->lado/2)) ||
		((elemento->x-elemento->lado/2 >= jogador->x-jogador->lado/2) && (jogador->x+jogador->lado/2 >= elemento->x-elemento->lado/2)))) return 1;
	else return 0;
}

void atualizaChefao(chefao *elemento, jogador *jogador) {

    if (colisaoInimigoJogador(elemento, jogador)) {
            jogador->vida -= 1;
        }

    

}

void desenhaChefao(chefao *elemento) {

}

void destroiChefao(chefao *elemento) {

}