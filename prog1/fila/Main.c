/* Nicolas Gabriel Ramos Pedroso GRR20204019 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Fila.h"



int main(){
    srand(time(NULL));
    struct fila f;
    int x;

    printf("Digite o tamanho do fila: ");
	scanf("%d", &x);

    if (x > MAXSIZE) {
        printf("Tamanho da fila excede o maximo permitido.\n");
        return 1; /*Saia do programa com codigo de erro*/ 
    }

    f = criaStructFila(x);

	f = aleatorioFila(f);

    printf("Valores da fila:\n");
    showQueue(f);
	printf("O elementos[0] fica de fora da contagem para ser usado como controle");
    printf("\n");

    do {
		printf("Digite o número da operação que deseja realizar\n");
        printf("1- Enqueue \n");
        printf("2- Dequeue \n");
        printf("3- Is Empty \n");
        printf("4- Is Full \n");
        printf("5- Show Queue \n");
        printf("6- Tamanho Queue \n");
		printf("7- Fim da Queue \n");
		printf("0- Finaliza o programa \n");
        

		scanf("%d", &x);
		/* Continue o codigo, mostrando ao usuario se X pertence a um, ambos ou 
		  *nenhum dos conjuntos, se X for um numero natural valido */

		switch (x){

			case 1:
				f = enqueue(f);
			break;

			case 2:
				f = dequeue(f);
			break;

			case 3:
				isEmptyFila(f) == 0 ? printf("Nao esta vazia a fila\n") : printf("Esta vazia a fila\n");
			break;

			case 4:
				isFullFila(f) == 0 ? printf("Nao esta cheia a fila\n") : printf("Esta cheia a fila\n");
			break;

            case 5:
				f = showQueue(f);
			break;

            case 6:
				printf("O tamanho da fila é:%d\n",tamanhoFila(f));
			break;

			case 7:
				printf("O final da fila é:%d\n", fim(f));
		}

	} while (x != 0);

    return 0;
}
