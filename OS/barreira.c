#include "barreira.h"

void barreira_init(Barreira *b, int total) {
    b->total = total;
    b->count = 0;
    sem_init(&b->mutex, 1, 1);
    sem_init(&b->turno, 1, 0);
}

void barreira_aguarda(Barreira *b) {
    sem_wait(&b->mutex);
    b->count++;
    if (b->count == b->total) {
        for (int i = 0; i < b->total; i++)
            sem_post(&b->turno);
        b->count = 0; // reutilizável
    }
    sem_post(&b->mutex);
    sem_wait(&b->turno);
}
