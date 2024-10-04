// #include "Ajuda.h"
// #include "Conjunto.h"
// #include "Lista.h"
// #include "Pilha.h"
#include <time.h>
#include <stdio.h>

int main() {

  int i, infelicidade, numCandidata, numPessoa, dadoCandidata, dadoPessoa, scoreCandidata, scorePessoa;
  int *atributosDesejados, 

  srand(tima(NULL));
  

  struct listaDE *l = inicializaLDE();
  struct listaDE *lp = inicializaLDE();
  struct listaDE *ps;/*pessoa selecionada*/
  struct pilha *p = inicializaPilha();
  struct pilha *cs;/*candidata selecionada*/

  printf("Digite o número de candidatas: ");
  scanf("%d", &numCandidata);
  printf("Digire o número de pessoas: ");
  scanf(" %d, &numPessoa");

  /*Funciona testado*/
  for (i = 0; i < numCandidata; i++) {
    push(p, i);
  }

  /*Funciona testado*/
  for (i = 0; i < numPessoa; i++) {
    insereCabeca(l, i);
  }
1
0  
  while((listaVazia(l) && pilhaVazia(p)) != false) {

  /*seleciona a candidata e aponta ela com o ponteiro cs*/  
  pop(p, cs);
  /*remove uma pessoa e coloca na lista de pretendentes lp*/
  removeCabeca(l, lp);
  
  if(!(subConjunto(cs->atributosDesejados, ps->atributos))){
    for( i = 0; i < 90; i++){
        dadoCandidata, dadoPessoa = rand() %20;

        if(dadoCandidata >= dadoPessoa){
            &scoreidata += scoreCandidata + 1;
        }else{
            &scorePessoa += scorePessoa + 1;
        }
    }
  }else{
    insereCauda(l, ps);
  }
  
  }

  printf("%d", )

  /*Dinâmica


Se houver um pretendente, desenfileirar e entrar no laço principal;

Se houver mais de um pretendente, cada um é desenfileirado para uma lista de
concorrentes e deve rolar 1d20 (dado de 20 faces, valor 1 a 20) por atributo em
comum, o maior ganha. A disputa de atributos é feita até que somente um
pretendente reste, entrando assim no laço principal. Os perdedores da disputa
são reinseridos na fila circular;

LAÇO PRINCIPAL

Por 90 iterações, a candidata e o pretendente tentam fazer uma ligação, isto é,
rolam 1d20 por atributo e acumulam “vitórias” (pontos de ligação);

Se ao fim das 90 iterações, a pessoa candidata acumulou mais pontos de ligação
do que o pretendente, ambos são retirados do jogo e um contador de match é
incrementado;

Senão, a pessoa candidata vai embora e o pretendente é reinserido na fila. Um
contador de mismatch é incrementado.

FINAL

O programa acaba quando não houver mais candidatas na pilha;

Os pretendentes remanescentes da fila circular são desenfileirados e incrementam
o contador de infelicidade;

Mostra-se os scores de quantas pessoas saíram infelizes/sem par, quantos pares
foram formados e quantos pares não deram certo.
*/
}