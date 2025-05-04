#include "fila_fifo.h"
#include <stdio.h>

void fila_init(FilaFIFO *f) {
    f->ini = f->fim = 0;
    sem_init(&f->mutex, 1, 1);
    for (int i = 0; i < MAX_FILA; i++) {
        sem_init(&f->espera[i], 1, 0);
    }
}

void inicia_uso(int recurso, FilaFIFO *f, int Pi) {
    sem_wait(&f->mutex);
    int pos = f->fim;
    f->fila[f->fim] = Pi;
    f->fim = (f->fim + 1) % MAX_FILA;

    if (f->ini == pos) {
        sem_post(&f->mutex);
        return;
    }
    sem_post(&f->mutex);
    sem_wait(&f->espera[pos]);
}

void termina_uso(int recurso, FilaFIFO *f) {
    sem_wait(&f->mutex);
    f->ini = (f->ini + 1) % MAX_FILA;

    if (f->ini != f->fim) {
        sem_post(&f->espera[f->ini]);
    }
    sem_post(&f->mutex);
}
