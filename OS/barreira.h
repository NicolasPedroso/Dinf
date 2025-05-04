#ifndef BARREIRA_H
#define BARREIRA_H

#include <semaphore.h>

typedef struct {
    int total;
    int count;
    sem_t mutex;
    sem_t turno;
} Barreira;

void barreira_init(Barreira *b, int total);
void barreira_aguarda(Barreira *b);

#endif
