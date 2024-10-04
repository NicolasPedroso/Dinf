#ifndef DICIONARIO_H
#define DICIONARIO_H

#define MAX_FILHOS 26
#define MAX_TAM_PALAVRA 100
#define MAX_RESULTADOS 20

typedef struct TrieNodo {
    struct TrieNodo* filho[MAX_FILHOS];
    int finalPalavra;
} TrieNodo;

TrieNodo* criaNodo();
void insere(TrieNodo* raiz, const char* palavra);
void busca(TrieNodo* raiz, const char* consulta, int maxEdicao, char** resultado, int* resultadoCount);
void liberaTrie(TrieNodo* raiz);
void adiciinaDicionario(TrieNodo* raiz, const char* filename);
void processaConsulta(TrieNodo* raiz, const char* filename);
void imprimePalavrasTrie(TrieNodo* raiz, char* buffer, int profundidade);

#endif