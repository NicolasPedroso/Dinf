#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "listaDupla.h"

// Verifica se a lista está vazia
void testa_listaVazia(struct listaDE *l){
        printf("A fila está vazia? %s\n", listaVazia(l) ? "Sim" : "Não");
}

// Insere e imprime um elemento no inicio da lista
void testa_insereCabeca(struct listaDE *l, int elemento){
        if (insereCabeca(l, elemento)){
                printf("\nO elemento %d foi inserido no início da lista", elemento);
        } else {
                printf("\nNão foi possível inserir o elemento na lista");
        }
}

// Insere e imprime um elemento no fim da lista
void testa_insereCauda(struct listaDE *l, int elemento){
        if (insereCauda(l, elemento)){
                printf("\nO elemento %d foi inserido no final da lista", elemento);
        } else {
                printf("\nNão foi possível inserir o elemento na lista");
    }
}

// Insere na lista ordenado em forma crescente
void testa_insereOrdenado(struct listaDE *l, int elemento){
        insereOrdenado(l, elemento);
}

// Retira e imprime o elemento do começo da lista
void testa_removeCabeca(struct listaDE *l) {
        int elemento;
        if (removeCabeca(l, &elemento)){
                printf("\nO elemento %d foi retirado do começo da lista", elemento); 
        } else {
                printf("\nNão foi possível retirar o elemento na lista");
        }
}

// Retira e imprime o elemento do começo da lista
void testa_removaCauda(struct listaDE *l) {
        int elemento;
        if (removeCauda(l, &elemento)){
                printf("\nO elemento %d foi retirado do final da lista", elemento); 
        } else {
                printf("\nNão foi possível retirar o elemento na lista");
        }
}

// Retira e Imprime um elemento especifico da lista
void testa_removeItem(struct listaDE *l, int elemento){
        if (removeItem(l, elemento)){
                printf("\n\nElemento %d foi encontrado e retirado da lista", elemento); 
        } else {
                printf("\nNão foi possível retirar o elemento na lista");
        }
}

// Impressão das funções de impressão
void impressao(struct listaDE *l) {
        imprimeCabeca(l);
        imprimeCauda(l);
        printf("\n");
        imprimeLDE(l);
}

// Função da para chamar o destroi
void destroiLista(struct listaDE *l) {
        destroiLDE(l);
}

// MAIN DO PROGRAMA
int main() {
        struct listaDE *l = inicializaLDE();
        struct item *itemSelecionado = criaItem(20);

        testa_listaVazia(l);

        testa_insereCabeca(l, 10);
        testa_insereCabeca(l, 20);
        testa_insereCabeca(l, 30);

        testa_removeCabeca(l);
        testa_removeCabeca(l);
        testa_removeCabeca(l);

        printf("\nTamanho atual da lista eh: %d\n", tamanhoLDE(l));

        testa_listaVazia(l);

        testa_insereCauda(l, 5);
        testa_insereCauda(l, 3);
        testa_insereCauda(l, 8);

        testa_removaCauda(l);
        testa_removaCauda(l);
        testa_removaCauda(l);

        printf("\nTamanho atual da lista eh: %d\n", tamanhoLDE(l));

        testa_listaVazia(l);

        testa_insereCauda(l, 1);
        testa_insereCauda(l, 10);
        testa_insereCauda(l, 2);
        testa_insereCauda(l, 9);
        testa_insereCauda(l, 3);
        testa_insereCauda(l, 8);
        testa_insereCauda(l, 4);
        testa_insereCauda(l, 7);
        testa_insereCauda(l, 5);
        testa_insereCauda(l, 6);
        

        testa_removeItem(l, 2);

        printf("\n\nTamanho atual da lista eh: %d\n", tamanhoLDE(l));

        testa_listaVazia(l);



        insereStruct(l, itemSelecionado);

        removeStruct(l, itemSelecionado);

        insereStruct(l, itemSelecionado);

        impressao(l);

        destroiLista(l);

        return 0;
}