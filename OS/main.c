#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/types.h>
#include "barreira.h"
#include "fila_fifo.h"
#include "utils.h"

#define N_PROC 15

int main() {
    int shm_barreira_id = shmget(IPC_PRIVATE, sizeof(Barreira), IPC_CREAT | 0600);
    int shm_fila_id = shmget(IPC_PRIVATE, sizeof(FilaFIFO), IPC_CREAT | 0600);
    if (shm_barreira_id < 0 || shm_fila_id < 0) {
        perror("shmget");
        exit(1);
    }

    Barreira *barreira = shmat(shm_barreira_id, NULL, 0);
    FilaFIFO *fila = shmat(shm_fila_id, NULL, 0);

    if (!barreira || !fila) {
        perror("shmat");
        exit(1);
    }

    srand(time(NULL));
    int recurso = rand() % 1000;

    barreira_init(barreira, N_PROC);
    fila_init(fila);

    for (int i = 0; i < N_PROC; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            int Pi = i;
            printf("--Processo: %d chegando na barreira\n", Pi);
            barreira_aguarda(barreira);
            printf("**Processo: %d saindo da barreira\n", Pi);

            for (int uso = 0; uso < 3; uso++) {
                int s = rand() % 4;
                printf("Processo: %d Prologo: %d de %d segundos\n", Pi, uso, s);
                sleep(s);

                inicia_uso(recurso, fila, Pi);
                s = rand() % 4;
                printf("Processo: %d USO: %d por %d segundos\n", Pi, uso, s);
                sleep(s);
                termina_uso(recurso, fila);

                s = rand() % 4;
                printf("Processo: %d Epilogo: %d de %d segundos\n", Pi, uso, s);
                sleep(s);
            }

            printf("--Processo: %d chegando novamente na barreira\n", Pi);
            barreira_aguarda(barreira);
            printf("++Processo: %d saindo da barreira novamente\n", Pi);

            exit(Pi);
        } 
    }

    for (int i = 0; i < N_PROC; i++) {
        int status;
        pid_t pid = wait(&status);
        int Pi = WEXITSTATUS(status);
        printf("+++ Filho de número lógico %d e pid %d terminou!\n", Pi, pid);
    }

    shmdt(barreira);
    shmdt(fila);
    shmctl(shm_barreira_id, IPC_RMID, NULL);
    shmctl(shm_fila_id, IPC_RMID, NULL);

    return 0;
}
