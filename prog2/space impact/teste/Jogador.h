#ifndef __JOGADOR__ 																																	//Guardas de inclusão
#define __JOGADOR__																																	//Guardas de inclusão																															//Quantidade de pixels que um quadrado se move por passo

#include "Controle.h"																																//Estrutura e procedimentos relacionados ao controle do quadrado
#include "Pistola.h" 																																//Estrutura e procedimentos relacionados ao controle da arma (pistola) no jogo

#define PASSO_JOGADOR 10																																//Tamanho, em pixels, de um passo do quadrado

typedef struct {																																	//Definição da estrutura de um quadrado
	unsigned char lado;																																//Tamanmho da lateral de um quadrado
	unsigned char face;																																//A face principal do quadrado, algo como a sua "frente"
	unsigned char vida;																																//Quantidade de vida do quadrado, em unidades (!)
	unsigned short x;																																//Posição X do centro do quadrado
	unsigned short y;																																//Posição Y do centro do quadrado
	controle *controle;																																//Elemento de controle do quadrado no jogo
	pistola *arma;																																	//Elemento para realizar disparos no jogo
} jogador;																																			//Definição do nome da estrutura

jogador* criaJogador(unsigned char lado, unsigned char face, unsigned short x, unsigned short y, unsigned short max_x, unsigned short max_y);		//Protótipo da função de criação de um quadrado
void moveJogador(jogador *elemento, char passos, unsigned char trajetoria, unsigned short max_x, unsigned short max_y);								//Protótipo da função de movimentação de um quadrado
void jogadorAtira(jogador *elemento);																													//Protótipo da função de disparo de um quadrado
void destroiJogador(jogador *elemento);																												//Protótipo da função de destruição de um quadrado

#endif																																				//Guardas de inclusão