/* Define as funções declaradas em pilha.h */
#include <stdlib.h>
#include <stdio.h>
#include "Pilha.h"
#include <stdbool.h>

// Recebe inteiro, aloca memoria para um itemP, atribui o valor e retorna o itemP
struct item *criaItem(int valor) {
        struct item *novo_item;

        if (!(novo_item = malloc(sizeof(struct item)))) { // aloca espaco na memoria para o itemP a ser adicionado
                return NULL;
        }

        novo_item->valor = valor; // criacao no valor passado pelo usuario dentro da pilha
        novo_item->proximo = NULL; // o proximo é 0 para ter controle

        return novo_item;
}

// Aloca memoria para uma pilha, zera o tamanho e atribui o ponteiros topo para NULO
struct pilha *inicializaPilha() {
        struct pilha *p;

        if (!(p = malloc(sizeof(struct pilha)))) { // aloca espaco na memoria para a pilha
                return NULL;
        }

        p->tamanho = 0; // tamanho inicializado com 0
        p->topo = NULL; // topo sendo 0 para controle

        return p;
}

// Retorna true para pilha vazia e false para pilha com ao menos um itemP
bool pilhaVazia(struct pilha *p) {
        if (p->topo == 0) {
                return true; // pilha vazia
        }
        return false; // pilha com ao menos um itemP
}


// Dada uma pilha P, insere itemP com valor x chamando criaItem no topo da pilha; 
// retorna 1 se x foi inserido com sucesso, 0 se x não foi inserido.
int push(struct pilha *p, int x) {
        struct item *novo = criaItem(x);

        if (novo == NULL) { // falha na alocacao de memoria
                return 0;
        }

        if (p->tamanho == 0) { // insere o primeiro elemento no topo

                p->topo = novo;
                p->topo->proximo = NULL;
                p->tamanho++;

                return 1; // empilhado com sucesso

        } else { // se já tiver um elemento

                novo->proximo = p->topo;
                p->topo = novo;
                p->tamanho++;

                return 1; // empilhado com sucesso
        }

        return 0; // pilha vazia, não é possível enfileirar
}

// Dada uma pilha P, remove elemento do topo, caso a pilha não esteja vazia; 
// retorna 1 se o elemento foi removido ou 0 se o elemento não foi removido.
// O ponteiro para inteiro 'dado' retorna o valor do topo...
int pop(struct pilha *p, int *dado) {
        struct item *dadoRemov; // criação do itemP de remocao

        // verifica pilha vazia e se falso realiza as operações de remover da pilha
        if (pilhaVazia(p) == false) {

                dadoRemov = p->topo; // comecar a remover do topo

                *dado = dadoRemov->valor; 
                p->topo = dadoRemov->proximo;

                free(dadoRemov); // liberacao da memoria alocada

                p->tamanho--;

                return 1;
        }
        return 0;
}

void imprimePilha(struct pilha *p) {
        struct item *aux;
        aux = p->topo;

        printf("Impressão dos elementos presentes na pilha: \n");

        while(aux) {
                printf("Elemento da pilha: %d\n", aux->valor);

                aux = aux->proximo;
        }
}

// Imprime o topo da pilha
void imprimeTopo(struct pilha *p) {
        if ((p != NULL) && (p->topo->valor != 0)) {
                printf("Topo da pilha: %d\n", p->topo->valor);
        } else {
                printf("Nao foi incializado ou está vazio\n");
        }
}

// Retorna o tamanho da pilha
int tamanhoPilha(struct pilha *p) {
        return (p->tamanho);
}

// Destroi cada itemP da pilha (se não vazia) e destroi a pilha
void destroiPilha(struct pilha *p) {
        // criacao de uma nova pilha que é a copia da que utilizamos para realizar as outras funcoes
        // alocar memória para a pilha nova
        struct item *dadoRemov;

        // verifica pilha vazia e se falso realiza as operações de infileirar na fila
        if (pilhaVazia(p) == false) {
                // destruir cada itemP
                // fazer um while que vai alocando um elemento por vez até todos estarem NULL
                while (p->tamanho != 0) {
                        dadoRemov = p->topo; 
                        p->topo = p->topo->proximo;

                        free(dadoRemov); // libera memoria que foi alocada do elemento

                        p->tamanho--;
                }

                printf("Pilha destruida\n");

        } else {

                printf("Pilha vazia\n");
        }

        free(p); // libera memoria que foi alocada do elemento
}

int pushStruct(struct pilha *p, struct item *i) {
        struct item *novo = i;

        if (novo == NULL) { // falha na alocacao de memoria
                return 0;
        }

        if (p->tamanho == 0) { // insere o primeiro elemento no topo

                p->topo = novo;
                p->topo->proximo = NULL;
                p->tamanho++;

                return 1; // empilhado com sucesso

        } else { // se já tiver um elemento

                novo->proximo = p->topo;
                p->topo = novo;
                p->tamanho++;

                return 1; // empilhado com sucesso
        }

        return 0; // pilha vazia, não é possível enfileirar
}

struct item* popStruct(struct pilha *p) {
        struct item *dadoRemov; // criação do itemP de remocao
        struct item *retorno; // cria item para retorno

        // verifica pilha vazia e se falso realiza as operações de remover da pilha
        if (pilhaVazia(p) == false) {

                dadoRemov = p->topo; // comecar a remover do topo

                retorno = dadoRemov; 
                p->topo = dadoRemov->proximo;

                free(dadoRemov); // liberacao da memoria alocada

                p->tamanho--;

                return retorno;
        }
        return NULL;
}
