#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Fila.h"

// Recebe inteiro, aloca memoria para um item, atribui o valor e retorna o item
struct item *criaItem(int valor){
    /*Verifica e aloca a memoria para o novo item*/
    struct item *novoItem;
    if(!(novoItem = malloc(sizeof(struct item))))
        return NULL;

    /*Atribui e devolve o novo item*/
    novoItem.valor = valor;
    return *novoItem;    
}

// Aloca memoria para uma fila e atribui os ponteiros inicio e fim para NULO
struct fila *inicializaFila(){

}

// Retorna true para fila vazia e false para fila com ao menos um item
bool filaVazia(struct fila *f);

// Dada uma fila F, insere item com valor x chamando criaItem no fim da fila; 
// retorna x se x foi enfileirado com sucesso, 0 se x não foi enfileirado...
int enfileira(struct fila *f, int x);

// Dada uma fila F, remove elemento do inicio, caso a fila não esteja vazia; 
// retorna o valor do elemento removido
int desenfileira(struct fila *f);

// Imprime o inicio da fila
void imprimeInicioDaFila(struct fila *f);

// Imprime o fim da fila
void imprimeFimDaFila(struct fila *f);

// Destroi cada item da fila (se não vazia) e destroi a fila
void destroiFila(struct fila *f){
    while(f.inicio == NULL){
        desenfileira(struct fila *f);
    }
    free(/*algo*/);
}