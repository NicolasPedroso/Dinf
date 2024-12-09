#ifndef __CONTROLE__
#define __CONTROLE__

typedef struct {
	unsigned char direita;
	unsigned char esquerda;
	unsigned char cima;
	unsigned char baixo;
	unsigned char atira;
} controle;

controle* criaControle();
void destroiControle(controle *elemento);
void controleDireita(controle *elemento);
void controleEsquerda(controle *elemento);
void controleCima(controle *elemento);
void controleBaixo(controle *elemento);
void controleAtira(controle *elemento);

#endif