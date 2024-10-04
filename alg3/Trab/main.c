#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Use: %s <nome do arquivo dicionario>\n", argv[0]);
        return EXIT_FAILURE;
    }
    TrieNodo* raiz = criaNodo();
    adiciinaDicionario(raiz, argv[1]);

    /*Imprime todas as palavras que estao na trie*/
    char buffer[MAX_TAM_PALAVRA];
    imprimePalavrasTrie(raiz, buffer, 0);

    processaConsulta(raiz, "consultas.txt");
    liberaTrie(raiz);
    return EXIT_SUCCESS;
}
