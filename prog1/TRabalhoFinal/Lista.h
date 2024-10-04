#include "Entidades.h"
#include <stdbool.h>


/* Nodo da lista */

struct nodo {
    struct pessoa Pretendente;
    struct pessoa *cabeca; /*ponteiro para o inicio da lista*/
    struct pessoa *cauda;  /*ponteiro para o fim da lista*/
    int tamanho;           /*tamanho da lista (numero de elementos na lista)*/  
};

/* Lista Duplamente Encadeada */
struct lista {
  struct nodo *Primeiro;
};


/* Para iniciar a lista deve-se zerar a cabeca e cauda */
struct lista *criarLista();

/* Testa se a lista esta vazia ou nao */
bool listaVazia(struct lista *l);

/* Insere x elementos na lista */
int insereCabecaQuantidade(struct lista *l, int x);

/* Insere o elemento no inicio da lista */
int insereCabeca(struct lista *l, struct pessoa *p);

/* Insere o elemento no final da lista */
int insereCauda(struct lista *l, struct pessoa *p);

/* Insere o elemento na lisra garantindo ordenacao em ordem crescente */
int insereOrdenado(struct lista *l, struct pessoa *p);

/* Remove elemento do inicio da lista */
int removeCabeca(struct lista *l, struct pessoa *p);

/* Remove elemento do final da lista */
int removeCauda(struct lista *l, struct pessoa *p);

/* Remove o elemento 'pessoa' caso ele exista na lista */
int removePessoa(struct lista *l, struct pessoa *p);

/* Imprime apenas a cabeca da lista */
void imprimeCabeca(struct lista *l);

/* Imprime apenas a cauda da lista */
void imprimeCauda(struct lista *l);

/* Imprime apenas a lista inteira */
void imprimeLista(struct lista *l);

/* Retorna o tamanho da lista */
int tamanhoLista(struct lista *l);

/*Remove todos os elementos da lista, libera espaco e retorna NULL*/
void destroiLista(struct lista *l);