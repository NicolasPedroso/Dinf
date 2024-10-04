#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Fila.h"



struct fila aleatorioFila(struct fila f){
	int i;

	for(i = 1; i < f.tamanho; i++){
		f.elementos[i] = rand()%100;
	}

    return f;
}

struct fila criaStructFila(int x){
    struct fila f;

    f.tamanho = x;
    f.fim = x;
    f.inicio = 1;
    f.elementos[0] = 0;

    return f;
}

bool isEmptyFila(struct fila f){
    if (f.inicio == f.fim ) return true;
}

bool isFullFila(struct fila f){
    if (f.fim == f.tamanho) return true;
}

bool overFlowFila(struct fila f){
    if (f.fim >= f.tamanho) return true;
}

bool underFlowFila(struct fila f){
    if (f.fim <= 0) return true;
}

struct fila queue(struct fila f) {
    int i;
    for (i = 1; i < f.fim - 1; i++) { 
        f.elementos[i] = f.elementos[i + 1];
    }
    return f;
}

struct fila enqueue(struct fila f){
    int x;

    if(overFlowFila(f) == false){
        f.fim = f.fim + 1;

        printf("Digite um novo valor para a fila\n");

        scanf("%d", &x);

        f.elementos[f.fim -1] = x;
    }
    else printf("Over Flow\n");

    return f;
}

struct fila dequeue(struct fila f){
    if(underFlowFila(f) == false){
        f = queue(f);
        f.fim = f.fim - 1;
    }
    else printf("Under Flow\n");

    return f;
}

int tamanhoFila(struct fila f){
    return f.tamanho;
}

int fim(struct fila f){
    return f.fim;
}

struct fila showQueue(struct fila f){
    int i;
    for (i = 1; i < f.fim; i++) {
        printf("%d ", f.elementos[i]);
    }
    printf("\n");
}
