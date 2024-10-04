#include <stdbool.h>

struct item {
	int valor;
	struct item *proximo;
};

struct pilha {
	struct item *topo;
	int tamanho;
};

// Recebe inteiro, aloca memoria para um item, atribui o valor e retorna o item
struct item *criaItem(int valor);

// Aloca memoria para uma pilha, zera o tamanho e atribui o ponteiros topo para NULO
struct pilha *inicializaPilha();

// Retorna true para pilha vazia e false para pilha com ao menos um item
bool pilhaVazia(struct pilha *p);

// Dada uma pilha P, insere item com valor x chamando criaItem no topo da pilha; 
// retorna 1 se x foi inserido com sucesso, 0 se x não foi inserido.
int push(struct pilha *p, int x);

// Dada uma pilha P, remove elemento do topo, caso a pilha não esteja vazia; 
// retorna 1 se o elemento foi removido ou 0 se o elemento não foi removido.
// O ponteiro para inteiro 'dado' retorna o valor do topo...
int pop(struct pilha *p, int *dado);

// Imprime o topo da pilha
void imprimeTopo(struct pilha *p);

// Retorna o tamanho da pilha
int tamanhoPilha(struct pilha *p);

// Destroi cada item da pilha (se não vazia) e destroi a pilha
void destroiPilha(struct pilha *p);

// Imprime os dados que estão dentro da pilha (fiz ela apenas para testes na main)
void imprimePilha(struct pilha *p);

// da push em um item recebido na pilha
// lembrar que é ponteiro e que não pode ser colocado varias vezes em sequencia sem tratar o pronteiro de entrada
int pushStruct(struct pilha *p, struct item *i);

// da pop na pilha e retorna um struct item
struct item* popStruct(struct pilha *p);