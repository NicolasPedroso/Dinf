#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pilha.h"



struct pilha aleatorioPilha(struct pilha p){
	int i;

	for(i = 1; i < p.tamanho; i++){
		p.elementos[i] = rand()%10;
	}

    return p;
}

struct pilha criaStructPilha(int x){
    struct pilha p;

    p.tamanho = x;
    p.topo = x;
    
    p.elementos[0] = 0;

    return p;
}

bool isEmptyPilha(struct pilha p){
    if (p.topo == 0 ) {
        return true;
    }else{
        return false;
    }
}

bool isFullPilha(struct pilha p){
    if (p.topo == p.tamanho) {
        return true;
    }else{
        return false;
    }
}

bool overFlowPilha(struct pilha p){
    if (p.topo >= p.tamanho) {
        return true;
    }else{
        return false;
    }
}

bool underFlowPilha(struct pilha p){
    if (p.topo <= 0) {
        return true;
    }else{
        return false;
    }
}

struct pilha push(struct pilha p){
    int x;

    if(overFlowPilha(p) == false){
        p.topo = p.topo + 1;

        printf("Digite um novo valor para a pilha\n");

        scanf("%d", &x);

        p.elementos[p.topo -1] = x;
    }
    else printf("Over Flow\n");

    return p;
}

struct pilha pop(struct pilha p){
    if(underFlowPilha(p) == false){
        p.topo = p.topo - 1;
    }
    else printf("Under Flow\n");

    return p;
}

int tamanhoPilha(struct pilha p){
    return p.tamanho;
}

int topo(struct pilha p){
    return p.topo;
}

struct pilha showPilha(struct pilha p){
    int i;
    for (i = 1; i < p.topo; i++) {
        printf("%d ", p.elementos[i]);
    }
    printf("\n");
}
