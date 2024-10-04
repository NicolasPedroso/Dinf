#include <stdbool.h>

struct item {
  int valor;  			// lista de numeros inteiros
  struct item *anterior;  // ponteiro para o proximo 
  struct item *proximo;	// ponteiro para o anterior
};

/* Lista Duplamente Encadeada */
struct listaDE {
  struct item *inicio;   // ponteiro para o inicio da lista
  struct item *fim;	   // ponteiro para o fim da lista
  int tamanho;		   // tamanho da lista (numero de elementos na lista)
};

// Cria um item para ser inserido na lista posteriormente
struct item *criaItem(int valor);

// Para iniciar a lista deve-se zerar a cabeca e cauda
struct listaDE *inicializaLDE();

// Testa se a lista está vazia ou não
bool listaVazia(struct listaDE *l);

// Insere o elemento no inicio da lista
int insereCabeca(struct listaDE *l, int x);

// Insere o elemento no inicio da lista
int insereStruct(struct listaDE *l, struct item *i);

// Insere o elemento no final da lista
int insereCauda(struct listaDE *l, int x);

// Insere o elemento na lisra garantindo ordenacao em ordem crescente
int insereOrdenado(struct listaDE *l, int x);

// Remove elemento do inicio da lista 
int removeCabeca(struct listaDE *l, int *dado);

// Remove o item do inicio da lista e retorna a struct removida
struct item *removeStruct(struct listaDE *l, struct item *i);

// Remove elemento do final da lista 
int removeCauda(struct listaDE *l, int *dado);

// Remove o elemento 'item' caso ele exista na lista
int removeItem(struct listaDE *l, int valor);

void imprimeCabeca(struct listaDE *l);

void imprimeCauda(struct listaDE *l);

void imprimeLDE(struct listaDE *l);

int tamanhoLDE(struct listaDE *l);

// Remove todos os elementos da lista, libera espaco e retorna NULL
void destroiLDE(struct listaDE *l);