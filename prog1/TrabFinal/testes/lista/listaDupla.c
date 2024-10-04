#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "listaDupla.h"

// Recebe inteiro, aloca memoria para um item, atribui o valor e retorna o item
struct item *criaItem(int valor) {
    struct item *novo_item;

    // Testa se tem lugar na memória reservado
    if (!(novo_item = malloc(sizeof(struct item)))) {
        return NULL;
    }

    novo_item->valor = valor;
    novo_item->anterior = NULL;
    novo_item->proximo = NULL;

    return novo_item;
}


// Para iniciar a lista deve-se zerar a cabeca e cauda
struct listaDE *inicializaLDE() {
        struct listaDE *l;

        // ele testa se tem lugar na memório reservado
        if (!(l = malloc(sizeof(struct listaDE)))) {
                return NULL;
        }

        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;

        return l;
}

// Retorna true para lista vazia e false para lista com ao menos um item
bool listaVazia(struct listaDE *l) {
        if ((l->tamanho) == 0) {
                return true;
        }
        return false;
}

// Insere o elemento no inicio da lista
int insereCabeca(struct listaDE *l, int x) {
    // aloca memoria para o novo elemento da lista a ser inserido
    struct item *novo = criaItem(x);

    if (novo == NULL)
        return 0; // falha na alocacao de memoria

    // verifica se a lista está vázia
    if (listaVazia(l)) { 
        l->inicio = novo;
        l->fim = novo;

        l->tamanho++;
        
        return 1; // inserido com sucesso
    } else {
        novo->proximo = l->inicio;
        l->inicio->anterior = novo;
        l->inicio = novo;
        l->tamanho++;
        
        return 1; // inserido com sucesso
    }

    // Não é necessário liberar memória aqui, pois o novo item foi inserido na lista
    return 0; // não é possível inserir
}

// Insere a struct item no inicio da lista
int insereStruct(struct listaDE *l, struct item *i) {
        // aloca memoria para o novo elemento da lista a ser inserido
        struct item *novo = i; 

        if (novo == NULL)
                return 0; // falha na alocacao de memoria

        // verifica se a lista está vázia
        if(listaVazia(l)) { 
                l->inicio = novo;
                l->fim = novo;

                l->tamanho++;
                
                return 1; // inserido com sucesso
        } else {
                
                novo->proximo = l->inicio;
                novo->anterior = NULL;
                l->inicio = novo;
                l->inicio->proximo->anterior = l->inicio;
                l->tamanho++;
                
                return 1; // inserido com sucesso
        }

        return 0; // não é possível inserir
}

// Insere o elemento no fim da lista
int insereCauda(struct listaDE *l, int x) {
    // aloca memoria para o novo elemento da lista a ser inserido
    struct item *novo = criaItem(x);

    if (novo == NULL) {
        return 0; // falha na alocacao de memoria
    }

    novo->valor = x;

    // verifica se a lista está vázia 
    if (listaVazia(l)){ 
        insereCabeca(l, x);
        
        // Precisamos liberar a memória do novo item se a inserção falhar
        free(novo);
        
        return 1; // inserido com sucesso no inicio
    } else {
        novo->anterior = l->fim;
        l->fim = novo;
        l->fim->anterior->proximo = l->fim;
        l->fim->proximo = NULL;

        l->tamanho++;
        return 1; // inserido com sucesso na fim
    }

    // Não é necessário liberar memória aqui, pois o novo item foi inserido na lista
    return 0; // não é possível inserir
}

// Insere o elemento na lista garantindo ordenacao em ordem crescente
int insereOrdenado(struct listaDE *l, int x) {
    struct item *novo = criaItem(x);

    if (novo == NULL) {
        return 0; // falha na alocação de memória
    }

    if (listaVazia(l)) {
        // lista vazia, insira o novo elemento como cabeça e cauda
        l->inicio = novo;
        l->fim = novo;
    } else if (x <= l->inicio->valor) {
        // insira o novo elemento como cabeça
        novo->proximo = l->inicio;
        l->inicio->anterior = novo;
        l->inicio = novo;
    } else if (x >= l->fim->valor) {
        // insira o novo elemento como cauda
        novo->anterior = l->fim;
        l->fim->proximo = novo;
        l->fim = novo;
    } else {
        // percorra a lista para encontrar a posição correta de inserção
        struct item *atual = l->inicio;

        while (atual->proximo && x > atual->proximo->valor) {
            atual = atual->proximo;
        }

        // inserir o novo elemento na posição correta da lista
        novo->proximo = atual->proximo;
        novo->anterior = atual;
        atual->proximo->anterior = novo;
        atual->proximo = novo;
    }

    l->tamanho++;
    return 1; // inserido com sucesso
}

int removeCabeca(struct listaDE *l, int *dado) {
    if (!(listaVazia(l))) {
        struct item *temp = l->inicio;
        *dado = temp->valor;
        l->inicio = l->inicio->proximo;

        if (l->inicio != NULL) {
            l->inicio->anterior = NULL;
        } else {
            // Se a lista ficou vazia após a remoção
            l->fim = NULL;
        }

        free(temp); // Libera a memória do item removido
        l->tamanho--;

        return 1;
    }
    return 0; // lista vazia
}

// Remove o primeiro struct item e retorna ele
struct item* removeStruct(struct listaDE *l, struct item *i) {
        // Cria o struc que será retornado
        struct item *retorno;

        if (!(listaVazia(l))) {
                retorno = l->inicio;
                l->inicio = l->inicio->proximo;
                l->tamanho--;

                return retorno;
        }
        return NULL; // lista vazia
}

// Remove elemento do final da lista 
int removeCauda(struct listaDE *l, int *dado) {
    if (!(listaVazia(l))) {
        *dado = l->fim->valor; 
        struct item *temp = l->fim;
        l->fim = l->fim->anterior; 
        if (l->fim != NULL) {
            l->fim->proximo = NULL;
        } else {
            // Se a lista ficou vazia após a remoção
            l->inicio = NULL;
        }

        free(temp); // Libera a memória do item removido
        l->tamanho--;

        return 1;
    }
    return 0; // lista vazia
}


// Remove o elemento caso ele exista na lista
int removeItem(struct listaDE *l, int valor) {
    struct item *atual = l->inicio;

    // verifica se a lista está vazia
    if (listaVazia(l)) {
        return 0; // não há elementos para retirar
    }

    // verifica se o elemento está no início
    if (l->inicio->valor == valor) {
        removeCabeca(l, &valor);
        return 1;
    }

    // verifica se o elemento está no fim
    if (l->fim->valor == valor) {
        removeCauda(l, &valor);
        return 1;
    }

    // percorre a lista até encontrar o elemento chave ou chegar ao fim da lista
    while (atual && atual->valor != valor) {
        atual = atual->proximo;
    }

    if (atual && atual->valor == valor) {
        if (atual->anterior) {
            atual->anterior->proximo = atual->proximo;
        }
        if (atual->proximo) {
            atual->proximo->anterior = atual->anterior;
        }

        // Atualiza l->inicio e l->fim se necessário
        if (l->inicio == atual) {
            l->inicio = atual->proximo;
        }
        if (l->fim == atual) {
            l->fim = atual->anterior;
        }

        free(atual);
        l->tamanho--;
        return 1;
    }

    return 0; // elemento não encontrado
}

// Imprime o inicio da lista
void imprimeCabeca(struct listaDE *l) {
        // testar se está vazia ou inicializada
        if ((l != NULL) && ((l->inicio->valor) != 0)) {
                printf("Inicio da lista: %d\n", l->inicio->valor);
        } else {
                printf("Nao foi incializado ou está vazio\n");
        }
}

// Imprime o fim da lista
void imprimeCauda(struct listaDE *l) {
        // testar se está vazia ou inicializada
        if ((l != NULL) && ((l->fim->valor) != 0)) {
                printf("Fim da lista: %d\n", l->fim->valor);
        } else {
                printf("Nao foi incializado ou está vazio\n");
        }
}

void imprimeLDE(struct listaDE *l) {
        struct item *aux;
        aux = l->inicio;

        printf("Impressão dos elementos presentes na lista: \n");

        while (aux != NULL) {
                printf("Elemento da fila: %d\n", aux->valor);
                aux = aux->proximo;
        }
}

int tamanhoLDE(struct listaDE *l) {
        return (l->tamanho);
}

// Remove todos os elementos da lista, libera espaco e retorna NULL
void destroiLDE(struct listaDE *l) {
        struct item *atual = l->inicio;
        struct item *proximo;

        while (atual != NULL) { // entra em um loop enquanto enquanto houver elementos na lista
                proximo = atual->proximo;
                free(atual);
                atual = proximo;
        }

        l->inicio = NULL;
        l->fim = NULL;
        free(l);

        printf("\nLista destruída com sucesso\n");
}