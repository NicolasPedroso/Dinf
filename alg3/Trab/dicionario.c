#include "dicionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Funcoes auxiliares*/
int min(int a, int b, int c) {
    int min = a < b ? a : b;
    return min < c ? min : c;
}

TrieNodo* criaNodo() {
    TrieNodo* nodo = (TrieNodo*)malloc(sizeof(TrieNodo));
    if (nodo) {
        nodo->finalPalavra = 0;
        for (int i = 0; i < MAX_FILHOS; i++) {
            nodo->filho[i] = NULL;
        }
    }
    return nodo;
}

/*Insere nodos na trie ignorando acentos e transformando letras maiusculas em minusculas*/
void insere(TrieNodo* raiz, const char* palavra) {
    TrieNodo* nodo = raiz;
    while (*palavra) {
        if (isalpha(*palavra)) {
            int index = tolower(*palavra) - 'a';
            if (!nodo->filho[index]) {
                nodo->filho[index] = criaNodo();
            }
            nodo = nodo->filho[index];
        }
        palavra++;
    }
    nodo->finalPalavra = 1;
}

/*Distancia Levenshtein*/
int distanciaEdicao(const char* palavra1, const char* palavra2) {
    int tam1 = strlen(palavra1);
    int tam2 = strlen(palavra2);
    int matriz[tam1 + 1][tam2 + 1];

    for (int i = 0; i <= tam1; i++) {
        for (int j = 0; j <= tam2; j++) {
            if (i == 0) {
                matriz[i][j] = j;
            } else if (j == 0) {
                matriz[i][j] = i;
            } else if (tolower(palavra1[i - 1]) == tolower(palavra2[j - 1])) {
                matriz[i][j] = matriz[i - 1][j - 1];
            } else {
                matriz[i][j] = 1 + min(matriz[i - 1][j], matriz[i][j - 1], matriz[i - 1][j - 1]);
            }
        }
    }
    /*Retorna posicao final da matriz e resultado da conta*/
    return matriz[tam1][tam2];
}

/*Percorre recursivamente a trie para encontrar palavras a maxEdicao da palavra de consulta*/
void ajudaBusca(TrieNodo* raiz, char* buffer, int profundidade, const char* consulta, int maxEdicao, char** resultado, int* resultadoCount) {
    if (!raiz) return;

    if (raiz->finalPalavra) {
        buffer[profundidade] = '\0';
        if (distanciaEdicao(buffer, consulta) <= maxEdicao) {
            resultado[*resultadoCount] = strdup(buffer);
            (*resultadoCount)++;
        }
    }

    for (int i = 0; i < MAX_FILHOS; i++) {
        if (raiz->filho[i]) {
            buffer[profundidade] = 'a' + i;
            ajudaBusca(raiz->filho[i], buffer, profundidade + 1, consulta, maxEdicao, resultado, resultadoCount);
        }
    }
}

/*Inicia o processo de busca na Trie utilizando a função auxiliar ajudaBusca; após "resultado" contera todas as palavras encontradas*/
void busca(TrieNodo* raiz, const char* consulta, int maxEdicao, char** resultado, int* resultadoCount) {
    char buffer[MAX_TAM_PALAVRA];
    *resultadoCount = 0;
    ajudaBusca(raiz, buffer, 0, consulta, maxEdicao, resultado, resultadoCount);
}

/*Apenas libera a memoria alocada para a trie*/
void liberaTrie(TrieNodo* raiz) {
    if (!raiz) return;
    for (int i = 0; i < MAX_FILHOS; i++) {
        liberaTrie(raiz->filho[i]);
    }
    free(raiz);
}

/*Faz leitura de um arquivo texto e adiciona ele a trie*/
void adiciinaDicionario(TrieNodo* raiz, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Falha ao abrir arquivo dicionário");
        exit(EXIT_FAILURE);
    }
    char palavra[MAX_TAM_PALAVRA + 1];  /*+1 para o caractere nulo*/
    while (fscanf(file, "%100s", palavra) != EOF) {
        if (strlen(palavra) >= MAX_TAM_PALAVRA) {
            int ch;
            /*Limpar o buffer de entrada ate o final da linha ou EOF*/
            /*Evita que apos palavras que passem MAX_TAM_PALAVRA sejam adicionadas por engano na lista*/
            while ((ch = fgetc(file)) != '\n' && ch != EOF);
            continue;
        }
        insere(raiz, palavra);
    }
    fclose(file);
}

/*Faz leitura de um arquivo texto de consulta e devolve resultados nele pedidos*/
void processaConsulta(TrieNodo* raiz, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Falha ao abrir arquivo de consultas, lembre-se de ter um arquivo consultas.txt");
        exit(EXIT_FAILURE);
    }
    char consulta[MAX_TAM_PALAVRA + 1]; 
    int maxEdicao;
    while (fscanf(file, "%100s %d", consulta, &maxEdicao) != EOF) {
        char* resultado[MAX_RESULTADOS];
        int resultadoCount = 0;
        busca(raiz, consulta, maxEdicao, resultado, &resultadoCount);
        printf("%s:", consulta);
        for (int i = 0; i < resultadoCount; i++) {
            printf("%s%s", resultado[i], (i < resultadoCount - 1) ? "," : "");
            free(resultado[i]);
        }
        printf("\n");
    }
    fclose(file);
}

/*Funcao que imprime todas as palavras na trie, boa para debugging do codigo*/
void imprimePalavrasTrie(TrieNodo* raiz, char* buffer, int profundidade) {
    if (!raiz) return;

    if (raiz->finalPalavra) {
        buffer[profundidade] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < MAX_FILHOS; i++) {
        if (raiz->filho[i]) {
            buffer[profundidade] = 'a' + i;
            imprimePalavrasTrie(raiz->filho[i], buffer, profundidade + 1);
        }
    }
}
