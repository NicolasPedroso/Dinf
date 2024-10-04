#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Pilha.h"

int main() {
        struct pilha *p = inicializaPilha();
        struct item *i = criaItem(2);
        int topo; // operacao de pop

        printf("A pilha está vazia? %s\n", pilhaVazia(p) ? "Sim" : "Não");

        push(p, 10);
        push(p, 20);
        push(p, 30);

        printf("Tamanho da pilha: %d\n", tamanhoPilha(p));

        if (pop(p, &topo)) {
                printf("Dado removido: %d\n", topo);
        } else {
                printf("A pilha está vazia, não foi possível remover um elemento.\n");
        }

        imprimePilha(p);

        printf("Começa o teste aqui");

        pushStruct(p, i);

        i = popStruct(p);

        printf("Valor do popStruct");
        printf("%d", i->valor);
        printf("%d", i->proximo);
        

        // imprimePilha(p);

        imprimeTopo(p);

        destroiPilha(p);

        return 0;
}