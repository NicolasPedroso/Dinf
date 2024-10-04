#include <stdbool.h>
#include "Conjunto.h"



struct candidata {
  int id;
  struct conjunto atributosDesejados; /*atributos de 1 - x que a cantidata querquando o valor eh 1*/
  struct candidata *proximo;
};

struct pilha {
    struct candidata *topo;
    int tamanho;
};

/* Recebe inteiro, aloca memoria para um candidata, atribui o valor e retorna o candidata */
struct candidata *criaCandidata(int valor);

/* Aloca memoria para uma pilha, zera o tamanho e atribui o ponteiros topo para NULO */
struct pilha *inicializaPilha();

/* Retorna true para pilha vazia e false para pilha com ao menos um candidata */
bool pilhaVazia(struct pilha *p);

/* Dada uma pilha P, insere candidata com valor x chamando criaCandidata no topo da pilha; 
   retorna 1 se x foi inserido com sucesso, 0 se x nao foi inserido. */
int push(struct pilha *p, int x);

/* Dada uma pilha P, remove elemento do topo, caso a pilha nao esteja vazia; 
   retorna 1 se o elemento foi removido ou 0 se o elemento nao foi removido.
   O ponteiro para inteiro 'dado' retorna o valor do topo... */
int pop(struct pilha *p, int *dado);

/* Imprime o topo da pilha */
void imprimeTopo(struct pilha *p);

/* Retorna o tamanho da pilha */
int tamanhoPilha(struct pilha *p);

/* Destroi cada candidata da pilha (se nao vazia) e destroi a pilha */
void destroiPilha(struct pilha *p);

/* Imprime os dados que estao dentro da pilha (fiz ela apenas para testes na main) */
void imprimePilha(struct pilha *p);
