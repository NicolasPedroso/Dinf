#define  MAXSIZE 256

#include <stdbool.h>

struct pilha {
    int topo;
    int tamanho; /* numero de elementos na fila */
    int elementos[MAXSIZE];
};

struct pilha criaStructPilha(int x);

bool isEmptyPilha(struct pilha P);

bool isFullPilha(struct pilha P);

bool overFlowPilha(struct pilha P);

bool underFlowPilha(struct pilha P);

struct pilha push(struct pilha P);

struct pilha pop(struct pilha P);

int tamanhoPilha(struct pilha P);

int topo(struct pilha P);

struct pilha showPilha(struct pilha P);

struct pilha aleatorioPilha(struct pilha P);
