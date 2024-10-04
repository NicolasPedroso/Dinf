#include <stdio.h>
#include "Conjunto.h"
#include "Ajuda.h"
#include <stdlib.h>



void main(){

    int operacao, escolha, x, i;

    struct conjunto *conjunto1;
	struct conjunto *conjunto2;
	struct conjunto *conjuntoAux;

	conjunto1 = criaConj();
	conjunto2 = criaConj();


	for ( i = 0 ; i < 10; i++){
		insereConj(conjunto1, 0);
	}

	/*conjunto1->elementos[9] = 1;*/

	for (i = 0; i < 3; i++) {
        int operacao = rand() % 9;
        conjunto1->elementos[operacao] = 1;
    }


	do{
        printf("Digite o numero do conjunto que deseja utilizar\n");
        printf("1- Conjunto 1 \n");
        printf("2- Conjunto 2 \n");
		printf("3- Comparacoes entre conjuntos \n");
        printf("0- Saida do programa \n");

		scanf("%d", &escolha);

        switch(escolha){

            case 1:
                
                do {
		            printf("Digite o numero da operacao que deseja realizar\n");
                    printf("1- Insere \n");
                    printf("2- Remove \n");
                    printf("3- Conjunto vazio \n");
                    printf("4- tamanho do conjunto \n");
                    printf("5- Pertence ao conjunto \n");
                    printf("6- Imprime conjunto \n");
		            printf("0- Finaliza o programa \n");


	    	        scanf("%d", &operacao);
	    	        /* Continue o codigo, mostrando ao usuario se X pertence a um, ambos ou 
	    	          *nenhum dos conjuntos, se X for um numero natural valido */

		            switch (operacao){

		    	        case 1:
							printf("Escolha um valor para adicionar do conjunto 1: ");
							scanf("%d", &x);
		    	    	    insereConj(conjunto1, x);
		    	        break;

		    	        case 2:
							printf("Escolha um valor para remover do conjunto 1: ");
							scanf("%d", &x);
		    	        	removeConj(conjunto1, x);
		    	        break;

		    	        case 3:
		    	        	conjVazio(conjunto1) == 0 ? printf("Nao esta vazio o conjunto\n") : printf("Esta vazio o conjunto\n");
		    	        break;

		    	        case 4:
							x = tamConj(conjunto1);
		    	        	printf("O tamanho do conjunto eh: %d\n", x);
		    	        break;

                        case 5:
							printf("Escolha um valor para ver se ele pertence ao conjunto 1: ");
							scanf("%d", &x);
		    	        	pertenceConj(conjunto1, x) == 0 ? printf("Pertence ao conjunto 1\n") : printf("Nao pertence ao conjunto 1\n");
		    	        break;

                        case 6:
		    	        	imprimeConj(conjunto1);
		    	        break;

						case 0:

						break;

		    	        default:
		    	        	printf("Operacao invalida digite novamente\n");
                        break;
		            }

	            }while(operacao != 0);
            
            break;

            case 2:

				do {
		            printf("Digite o numero da operacao que deseja realizar\n");
                    printf("1- Insere \n");
                    printf("2- Remove \n");
                    printf("3- Conjunto vazio \n");
                    printf("4- tamanho do conjunto \n");
                    printf("5- Pertence ao conjunto \n");
                    printf("6- Imprime conjunto \n");
		            printf("0- Finaliza o programa \n");


	    	        scanf("%d", &operacao);

		            switch (operacao){

		    	        case 1:
							printf("Escolha um valor para adicionar do conjunto 2: ");
							scanf("%d", &x);
		    	    	    insereConj(conjunto2, x);
		    	        break;

		    	        case 2:
							printf("Escolha um valor para remover do conjunto 2: ");
							scanf("%d", &x);
		    	        	removeConj(conjunto2, x);
		    	        break;

		    	        case 3:
		    	        	conjVazio(conjunto2) == 0 ? printf("Nao esta vazio o conjunto\n") : printf("Esta vazio o conjunto\n");
		    	        break;

		    	        case 4:
							x = tamConj(conjunto2);
		    	        	printf("O tamanho do conjunto eh: %d\n", x);
		    	        break;

                        case 5:
							printf("Escolha um valor para ver se ele pertence ao conjunto 2: ");
							scanf("%d", &x);
		    	        	pertenceConj(conjunto2, x) == 0 ? printf("Pertence ao conjunto 2\n") : printf("Nao pertence ao conjunto 2\n");
		    	        break;

                        case 6:
		    	        	imprimeConj(conjunto2);
		    	        break;

						case 0:

						break;

		    	        default:
		    	        	printf("Operacao invalida digite novamente/n");
                        break;
		            }

	            }while(operacao != 0);

            break;

			case 3:
			
				do {
		            printf("Digite o numero da operacao que deseja realizar\n");
                    printf("1- Intersecao \n");
                    printf("2- Uniao \n");
					printf("3- Subconjunto \n");
		            printf("0- Finaliza o programa \n");


	    	        scanf("%d", &operacao);

		            switch (operacao){

		    	        case 1:
							conjuntoAux = intersecao(conjunto1, conjunto2);
							imprimeConj(conjuntoAux);
							destroiConj(conjuntoAux);
		    	        break;

		    	        case 2:
							conjuntoAux = uniao(conjunto1, conjunto2);
							imprimeConj(conjuntoAux);
							destroiConj(conjuntoAux);
		    	        break;

						case 3:
							subConjunto(conjunto1, conjunto2) == 0 ? printf("Conjunto1 eh subconjunto do conjunto2\n") : printf("Conjunto1 nao eh subconjunto do conjunto2\n");
		    	        break;

						case 0:

						break;

		    	        default:
		    	        	printf("Operacao invalida digite novamente/n");
                        break;
		            }

	            }while(operacao != 0);

			break;
        }

    }while(escolha != 0);
	
	destroiConj(conjunto1);
	destroiConj(conjunto2);
	
}