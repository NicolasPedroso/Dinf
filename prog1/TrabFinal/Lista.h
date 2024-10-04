#include <stdbool.h>

struct pessoa {
  int id;
  struct conjunto
      atributos; /*atributos de 1 - x que a pessoa tem quando o valor eh 1*/
  int infelicidade;
  struct pessoa *anterior;
  struct pessoa *proximo;
};

/* Lista Duplamente Encadeada */
struct listaDE {
  struct pessoa *cabeca;   /*ponteiro para o inicio da lista*/
  struct pessoa *cauda;	   /*ponteiro para o fim da lista*/
  int tamanho;		   /*tamanho da lista (numero de elementos na lista)*/
};

/*Cria uma pessoa para ser inserido na lista posteriormente*/
struct pessoa *criaPessoa(int valor);

/*Para iniciar a lista deve-se zerar a cabeca e cauda*/
struct listaDE *inicializaLDE();

/*Testa se a lista esta vazia ou nao*/
bool listaVazia(struct listaDE *l);

/*Insere o elemento no inicio da lista*/
int insereCabeca(struct listaDE *l, int x);

/*Insere o elemento no final da lista*/
int insereCauda(struct listaDE *l, int x);

/*Insere o elemento na lisra garantindo ordenacao em ordem crescente*/
int insereOrdenado(struct listaDE *l, int x);

/*Remove elemento do inicio da lista */
int removeCabeca(struct listaDE *l, int *dado);

/*Remove elemento do final da lista*/ 
int removeCauda(struct listaDE *l, int *dado);

/*Remove o elemento 'pessoa' caso ele exista na lista*/
int removePessoa(struct listaDE *l, int valor);

void imprimeCabeca(struct listaDE *l);

void imprimeCauda(struct listaDE *l);

void imprimeLDE(struct listaDE *l);

int tamanhoLDE(struct listaDE *l);

/*Remove todos os elementos da lista, libera espaco e retorna NULL*/
void destroiLDE(struct listaDE *l);