/* Nicolas Gabriel Ramos Pedroso GRR20204019 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Fila.h"
#include "Pilha.h"



int main(){
    srand(time(NULL));
    struct fila f;
    struct pilha p;
    int x;

	printf("O elementos[0] fica de fora da contagem para ser usado como controle");
    printf("\n");

    do{
        printf("Digite o numero da estrutura que deseja utilizar\n");
        printf("1- Pilha \n");
        printf("2- Fila \n");
        printf("3- Saida do programa \n");

		scanf("%d", &x);

        switch (x) {

            case 1:

                printf("Digite o tamanho do pilha: ");
	            scanf("%d", &x);
                        
                if (x > MAXSIZE) {
                    printf("Tamanho da pilha excede o maximo permitido.\n");
                    return 1;  
                }
                p = criaStructPilha(x);
                p = aleatorioPilha(p);


                
                do {
		            printf("Digite o numero da operacao que deseja realizar\n");
                    /*printf("0- Cria pilha \n"); eh possivel fazer isso mas eh necessario verificar antes de qualquer outra acao*/
                    printf("1- Push \n");
                    printf("2- Pop \n");
                    printf("3- Is Empty \n");
                    printf("4- Is Full \n");
                    printf("5- Show pilha \n");
                    printf("6- Tamanho pilha \n");
	    	        printf("7- Topo da pilha \n");
		            printf("0- Finaliza o programa \n");


	    	        scanf("%d", &x);
	    	        /* Continue o codigo, mostrando ao usuario se X pertence a um, ambos ou 
	    	          *nenhum dos conjuntos, se X for um numero natural valido */

		            switch (x){
                        
                        /*case 0:
                            printf("Digite o tamanho do pilha: ");
	                        scanf("%d", &x);

                            if (x > MAXSIZE) {
                                printf("Tamanho da pilha excede o maximo permitido.\n");
                                return 1;  
                            }

                            p = criaStructPilha(x);

                    	    p = aleatorioPilha(p);
                        break;*/


		    	        case 1:
		    	    	    p = push(p);
		    	        break;

		    	        case 2:
		    	        	p = pop(p);
		    	        break;

		    	        case 3:
		    	        	isEmptyPilha(p) == 0 ? printf("Nao esta vazia a pilha\n") : printf("Esta vazia a pilha\n");
		    	        break;

		    	        case 4:
		    	        	isFullPilha(p) == 0 ? printf("Nao esta cheia a pilha\n") : printf("Esta cheia a pilha\n");
		    	        break;

                        case 5:
		    	        	p = showPilha(p);
		    	        break;

                        case 6:
		    	        	printf("O tamanho da pilha eh:%d\n",tamanhoPilha(p));
		    	        break;

		    	        case 7:
		    	        	printf("O topo da pilha eh:%d\n", topo(p));
                        break;
		            }

	            } while (x != 0);
            
            break;

            case 2:

                printf("Digite o tamanho do fila: ");
	            scanf("%d", &x);

                if (x > MAXSIZE) {
                    printf("Tamanho da fila excede o maximo permitido.\n");
                    return 1;  
                }

                f = criaStructFila(x);

                f = aleatorioFila(f);

                do {
	            	printf("Digite o número da operação que deseja realizar\n");
                    /*printf("0- Cria fila \n"); eh possivel fazer isso mas eh necessario verificar antes de qualquer outra acao*/
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

	            	switch (x) {
                    
                        /*case 0:
                            printf("Digite o tamanho do fila: ");
	                        scanf("%d", &x);

                            if (x > MAXSIZE) {
                                printf("Tamanho da fila excede o maximo permitido.\n");
                                return 1;  
                            }

                            f = criaStructFila(x);

                    	    f = aleatorioFila(f);
                        break;*/

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

            break;
        }

    } while (x != 3);

    return 0;
}
