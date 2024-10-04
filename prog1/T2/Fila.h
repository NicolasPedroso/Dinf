#define  MAXSIZE 256

#include <stdbool.h>

struct fila {
    int inicio;
    int fim;
    int tamanho; /* numero de elementos na fila */
    int elementos[MAXSIZE];
};

struct fila criaStructFila(int x);

bool isEmptyFila(struct fila F);

bool isFullFila(struct fila F);

bool overFlowFila(struct fila F);

bool underFlowFila(struct fila F);

struct fila queue(struct fila F);

struct fila enqueue(struct fila F);

struct fila dequeue(struct fila F);

int tamanhoFila(struct fila F);

int fim(struct fila F);

struct fila showQueue(struct fila F);

struct fila aleatorioFila(struct fila F);
