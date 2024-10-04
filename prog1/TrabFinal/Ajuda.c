#include <stdlib.h>
#include "Conjunto.h"

/*Busca binaria que retorna a posicao do elemento ou -1 para erro*/
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
}
