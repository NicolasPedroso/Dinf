#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vetorAlet(int v[], int min, int max, int elementos){
    for(int i = 0; i < elementos; i++){
        v[i] = min + (rand() % max);   
    } 
}

void imprimeVetor(int v[], int elementos){
    for(int i = 0; i < elementos; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

void criaVetor(int **v, int elementos){
    *v = (int *)(malloc(elementos * sizeof(int)));
    
    if(*v == NULL){
        printf("\nErro ao alocar memoria");
        exit(1);
    }
    
    for(int i = 0; i < elementos; i++){
        (*v)[i] = 1;
    }
}

void leVetor(int v[], int elementos){
    for(int i = 0; i < elementos; i++){
        printf("Digite o valor do vetor:\n");
        scanf("%d", &v[i]);
    }
}

void copiaVetor(int b[], int c[], int n){
    for(int i = 0; i < n; i++){
        c[i] = b[i];
    }
}

void main(){
    int elementos;
    int *v;
    srand(time(NULL));

    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &elementos);

    criaVetor(&v, elementos);
    vetorAlet(v, 1, 100, elementos); /* 1 é o min e 20 max*/
    imprimeVetor(v, elementos);
    //leVetor(v, elementos);
    imprimeVetor(v, elementos);

    free(v);
}