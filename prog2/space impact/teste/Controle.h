#ifndef __CONTROLE__ 																												//Guardas de inclusão 
#define __CONTROLE__																												//Guardas de inclusão 

typedef struct {																													//Definição da estrutura de um controle 
	unsigned char direita;																											//Botão de movimentação à direta 
	unsigned char esquerda;																												//Botão de movimentação à esquerda 
	unsigned char cima;																												//Botão de movimentação para cima 
	unsigned char baixo;																												//Botão de disparo																											//Botão de movimentação para baixo 
	unsigned char atira;
} controle;																															//Definição do nome da estrutura 

controle* criaControle();																										//Protótipo da função de criação de um controle 
void destroiControle(controle *elemento);																							//Protótipo da função de destruição de um controle 
void controleDireita(controle *elemento);																								//Protótipo da função de ativação/desativação do botão de movimentação à direita 
void controleEsquerda(controle *elemento);																								//Protótipo da função de ativação/desativação do botão de movimentação à esquerda 
void controleCima(controle *elemento);																								//Protótipo da função de ativação/desativação do botão de movimentação para cima 
void controleBaixo(controle *elemento);																								//Protótipo da função de ativação/desativação do botão de movimentação para baixo 
void controleAtira(controle *elemento);																								//Protótipo da função de ativação/desativação do botão de disparo

#endif																																//Guardas de inclusão 