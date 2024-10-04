#include "Conjunto.h"
#include "Ajuda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Busca binaria que retorna a posicao do elemento ou -1 para erro */
int buscaBinaria(struct conjunto *c, int x) {
        int inicio, fim, i;
        inicio = 0;
        fim = c->tam;
        while (fim > inicio) {
                i = (inicio + fim) / 2;
                if (*(c->elementos+i) == x) return i;
                if (*(c->elementos+i) < x) inicio = i + 1;
                else fim = i;
        }
        return -1;

  /*Colocar funções para lidar com vetor aqui também*/
}

void vetorAlet(int v[], int min, int max, int elementos){
    int i;
    for(i = 0; i < elementos; i++){
        v[i] = min + (rand() % max);   
    } 
}