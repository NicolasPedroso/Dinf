#ifndef FILA_FIFO_H
#define FILA_FIFO_H

#include <semaphore.h>

#define MAX_FILA 32

typedef struct {
    int fila[MAX_FILA];
    int ini, fim;
    sem_t mutex;
    sem_t espera[MAX_FILA];
} FilaFIFO;

void fila_init(FilaFIFO *f);
void inicia_uso(int recurso, FilaFIFO *f, int Pi);
void termina_uso(int recurso, FilaFIFO *f);

#endif
