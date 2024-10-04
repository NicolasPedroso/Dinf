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


void copiaVetor(int b[], int c[], int n){
    for(int i = 0; i < n; i++){
        c[i] = b[i];
    }
}


void lePresente(int v[], int p[], int elementos){
    for(int i = 0; i < elementos; i++){
        printf("Digite o valor sentimental do presente:\n");
        scanf("%d", &v[i]);
        printf("Digite o peso do presente:\n");
        scanf("%d", &p[i]);
    }
}



void vetBinario(int b[], int n, int i, int p[], int pesoMax, int v[], int c[], int *sentimento, int *peso){
    if(i == n){
        int pesoTotal = 0;
        int sentimentoTotal = 0;
        for(int j = 0; j < n; j++){
            if(b[j] == 1){
                pesoTotal += p[j];
                sentimentoTotal += v[j];
            }
        }
        if(sentimentoTotal >= *sentimento && pesoTotal <= pesoMax){
            *sentimento = sentimentoTotal;
            *peso = pesoTotal;
            copiaVetor(b, c, n);
        }
        return;
    }
    b[i] = 1;
    vetBinario(b, n, i+1, p, pesoMax, v, c, sentimento, peso);
    b[i] = 0;
    vetBinario(b, n, i+1, p, pesoMax, v, c, sentimento, peso);
}




int main() {


    srand(time(NULL));
    
    clock_t start, end;
    double tempo;

    int elementos, pesoMax, sentimento = 0, peso = 0;
    int *b, *v, *p, *c;
    printf("Digite a quantidade de presentes:\n");
    scanf("%d", &elementos);
    printf("Digite peso maximo do saco do papai noel:\n");
    scanf("%d", &pesoMax);
    
    start = clock();

    criaVetor(&b, elementos);
    criaVetor(&c, elementos);
    criaVetor(&v, elementos);
    vetorAlet(v, 1, 20, elementos); /* 1 é o min e 20 max*/
    criaVetor(&p, elementos);
    vetorAlet(p, 1, 15, elementos); /* 1 é o min e 100 max*/
    printf("\n");
    //lePresente(v, p, elementos); /* tirar o comentario para colocar dados manualmente */
    printf("\n");
    vetBinario(b, elementos, 0, p, pesoMax, v, c, &sentimento, &peso);
    printf("\n");
    printf("Peso total dos presentes: %d\n", peso);
    printf("Valor sentimental dos presentes: %d\n", sentimento);
    
    printf("Vetor com os presentes que devem ser escolhidos\n");
    imprimeVetor(c, elementos);
    printf("\n");
    
    
    free(b);
    free(v);
    free(p);
    free(c);

    end = clock();

    tempo = ((double) end - start)/CLOCKS_PER_SEC;

    printf("\nTempo total:%f\n", tempo);   

    return 0;
}