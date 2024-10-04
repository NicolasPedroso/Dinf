#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Lista.h"
#include "Conjunto.h"

/*Recebe inteiro, aloca memoria para um item, atribui o valor e retorna o item*/
struct pessoa *criaPessoa(int valor) {
        struct item *novoPessoa;
        
        /*ele testa se tem lugar na memorio reservado*/
        if (!(novoPessoa = malloc(sizeof(struct pessoa)))) {
                return NULL;
        }

        novoPessoa->id = valor;
        /*Adicionar aqui */
        novoPessoa->anterior = NULL;
        novoPessoa->proximo = NULL;

        return novoPessoa;
}

/*Para iniciar a lista deve-se zerar a cabeca e cauda*/
struct listaDE *inicializaLDE() {
        struct listaDE *l;

        /*ele testa se tem lugar na memorio reservado*/
        if (!(l = malloc(sizeof(struct listaDE)))) {
                return NULL;
        }

        l->cabeca = NULL;
        l->cauda = NULL;
        l->tamanho = 0;

        return l;
}

/*Retorna true para lista vazia e false para lista com ao menos um item*/
bool listaVazia(struct listaDE *l) {
        if ((l->tamanho) == 0) {
                return true;
        }
        return false;
}

int insereCabeca(struct listaDE *l, int x) {
    if (!listaVazia(l)) {
        struct item *novo = criaItem(x);

        if (novo == NULL)
            return 0; /*falha na alocacao de memoria*/

        novo->proximo = l->cabeca;
        novo->anterior = NULL;
        novo->valor = x;

        l->cabeca->anterior = novo;
        l->cabeca = novo;
        l->tamanho++;

        return 1; /*inserido com sucesso*/
    }

    return 0; /*nao e possivel inserir*/
}

int insereCauda(struct listaDE *l, int x) {
    if (!listaVazia(l)) {
        struct item *novo = criaItem(x);

        if (novo == NULL)
            return 0; /*falha na alocacao de memoria*/

        novo->valor = x;
        novo->anterior = l->cauda;

        l->cauda->proximo = novo;
        l->cauda = novo;
        l->tamanho++;

        return 1; /*inserido com sucesso na cauda*/
    }

    return 0; /*nao e possivel inserir*/
}

/*Insere o elemento na lista garantindo ordenacao em ordem crescente*/
int insereOrdenado(struct listaDE *l, int x) {
        struct item *novo = criaItem(x);

        if (novo == NULL) {
                return 0; /*falha na alocacao de memoria*/
        }

        if (listaVazia(l)) {
                /*lista vazia, insira o novo elemento como cabeca e cauda*/
                l->cabeca = novo;
                l->cauda = novo;
                printf("\n%d Primeiro elemento inserido na lista", novo->valor);
                
        } else if (x <= l->cabeca->valor) {
                /*insira o novo elemento como cabeca*/
                novo->proximo = l->cabeca;
                l->cabeca->anterior = novo;
                l->cabeca = novo;
                printf("\n%d elemento inserido na cabeca", novo->valor);
                
        } else if (x >= l->cauda->valor) {
                /*insira o novo elemento como cauda*/
                novo->anterior = l->cauda;
                l->cauda->proximo = novo;
                l->cauda = novo;
                printf("\n%d elemento inserido na cauda", novo->valor);
                
        } else {
                /*percorra a lista para encontrar a posicao correta de insercao*/
                struct item *atual = l->cabeca;

                while (atual->proximo && x > atual->proximo->valor) {
                        atual = atual->proximo;
                }

                /*inserir o novo elemento na posicao correta da lista*/
                novo->proximo = atual->proximo;
                novo->anterior = atual;
                atual->proximo->anterior = novo;
                atual->proximo = novo;
                printf("\n%d elemento inserido na posicao correta", novo->valor);
        }

        l->tamanho++;
        return 1; /*inserido com sucesso*/
}


/*Remove elemento do inicio da lista*/ 
int removeCabeca(struct listaDE *l, int *dado) {
        if (!(listaVazia(l))) {
                *dado = l->cabeca->valor;
                l->cabeca = l->cabeca->proximo;
                l->tamanho--;

                return 1;
        }
        return 0; /*lista vazia*/
}

/*Remove elemento do final da lista*/ 
int removeCauda(struct listaDE *l, int *dado) {
        if (!(listaVazia(l))) {
                *dado = l->cauda->valor; 
                l->cauda = l->cauda->anterior; 
                l->tamanho--;

                return 1;
        }
        return 0; /*lista vazia*/
}

/*Remove o elemento caso ele exista na lista*/
/* Remove o elemento caso ele exista na lista */
/* Remove o elemento caso ele exista na lista */
/* Remove o elemento caso ele exista na lista */
int removeItem(struct listaDE *l, int valor) {
    struct item *aux = l->cabeca;

    if (listaVazia(l)) {
        return 0; /* Não há elementos para retirar */
    }

    /* Verifica se o elemento está no início */
    if (l->cabeca->valor == valor) {
        removeCabeca(l, &valor);
        return 1;
    }

    /* Verifica se o elemento está no fim */
    if (l->cauda->valor == valor) {
        removeCauda(l, &valor);
        return 1;
    }

    /* Percorre a lista até achar o elemento chave ou até o fim da lista */
    while (aux != NULL && aux->valor != valor) {
        aux = aux->proximo;
    }

    if (aux != NULL) {
        if (aux->anterior != NULL) {
            aux->anterior->proximo = aux->proximo;
        } else {
            return 0; // O elemento a ser removido não foi encontrado na lista
        }

        if (aux->proximo != NULL) {
            aux->proximo->anterior = aux->anterior;
        } else {
            l->cauda = aux->anterior; // Atualiza a cauda se o último elemento foi removido
        }

        free(aux);
        l->tamanho--;

        return 1;
    }

    return 0; /* Elemento não encontrado na lista */
}


/*Imprime o inicio da lista*/
void imprimeCabeca(struct listaDE *l) {
        /*testar se esta vazia ou inicializada*/
        if ((l != NULL) && ((l->cabeca->valor) != 0)) {
                printf("Inicio da lista: %d\n", l->cabeca->valor);
        } else {
                printf("Nao foi incializado ou está vazio\n");
        }
}

/*Imprime o fim da lista*/
void imprimeCauda(struct listaDE *l) {
        /*testar se esta vazia ou inicializada*/
        if ((l != NULL) && ((l->cauda->valor) != 0)) {
                printf("Fim da lista: %d\n", l->cauda->valor);
        } else {
                printf("Nao foi incializado ou está vazio\n");
        }
}

void imprimeLDE(struct listaDE *l) {
        struct item *aux;
        aux = l->cabeca;

        printf("Impressão dos elementos presentes na lista: \n");

        while (aux != NULL) {
                printf("Elemento da fila: %d\n", aux->valor);
                aux = aux->proximo;
        }
}

int tamanhoLDE(struct listaDE *l) {
        return (l->tamanho);
}

/*Remove todos os elementos da lista, libera espaco e retorna NULL*/
void destroiLDE(struct listaDE *l) {
    struct item *atual = l->cabeca;
    struct item *proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(l);

    printf("\nLista destruída com sucesso\n");
}

