#include "Conjunto.h"
#include "Ajuda.h"
#include <stdio.h>
#include <stdlib.h>

/*Retorna um ponteira do tipo struct conjunto*/
struct conjunto *criaConj() {
  struct conjunto *conj;

  /*Inicio o conjunto em si*/
  if ((conj = malloc(sizeof(struct conjunto)))) {
    conj->maxTam = 1;
    conj->tam = 0;

    /*Inicio o vetor para os elementos*/
    if ((conj->elementos = (int *)malloc(sizeof(int) * (conj->maxTam + 1))))
      return conj;
    else {
      free(conj);
      return NULL;
    }
  } else
    return NULL;
}

/*Da free na memoria alocada*/
void destroiConj(struct conjunto *c) {
  /*Free no vetor*/
  free(c->elementos);
  /*Free no conjunto*/
  free(c);
}

/*Retorna o tamanho do conjunto que precisa ser atribuido para um variavel*/
int tamConj(struct conjunto *c) { return c->tam; }

/*Verifica se o elemento x pertence ao conjunto C, se esta no conjunto devolve a
 * pocisao do contrario devolve -1*/
bool pertenceConj(struct conjunto *c, int x) {
  if (buscaBinaria(c, x) == -1)
    return true;
  return false;
}
/*Verifica se c1 eh subconjunto de c2*/
bool subConjunto(struct conjunto *c1, struct conjunto *c2) {
  int i;
  if (c1->tam > c2->tam)
    return false;
  else {
    for (i = 0; i < c1->tam; i++)
      if (!pertenceConj(c2, *(c1->elementos + i)))
        return false;
    return true;
  }
}

/* Insere o elemento x ao conjunto C, caso x nao exista em C */
void insereConj(struct conjunto *c, int x) {
  int i;

  /*Verifica se pertence ao conjunto*/
  if (!(pertenceConj(c, x)))
    return;

  if (c->tam == c->maxTam) {
    /*Redimensiona o conjunto se estiver cheio*/
    int novoMaxTam = c->maxTam + 1;
    int *novosElementos = (int *)malloc(sizeof(int) * novoMaxTam);
    if (novosElementos == NULL) {
      printf("Falha ao alocar memoria\n");
      return;
    }

    for (i = 0; i < c->tam; i++) {
      novosElementos[i] = c->elementos[i];
    }

    /*Libera o antigo ponteiro e coloca o novo nele*/
    free(c->elementos);
    c->elementos = novosElementos;
    /*Atualiza o maxTam*/
    c->maxTam = novoMaxTam;
  }

  /*coloca o novo elemento em ordem percorrendo o vetor de tras para frente*/
  for (i = c->tam - 1; i >= 0; i--) {
    if (x < c->elementos[i]) {
      c->elementos[i + 1] = c->elementos[i];
    } else {
      break;
    }
  }

  c->elementos[i + 1] = x;
  c->tam++;
}

/*Remove o elemento e diminiu o maxTam do conjunto*/
void removeConj(struct conjunto *c, int x) {
  int pos, i;

  /*Verifica se o elemento existe para ser removido*/
  if ((pos = buscaBinaria(c, x)) != -1) {
    pos = pos + 1;
    /*Moveme os elementos da posicao+1 para posicao assim remomendo o elemento*/
    for (i = pos; i < c->tam; i++)
      *(c->elementos + i - 1) = *(c->elementos + i);
    c->tam--;
    return;
  }
  return;
}

/*Retorna conjunto de tamanho alocado maximo tamConj(c1) + tamConj(c2)*/
struct conjunto *uniao(struct conjunto *c1, struct conjunto *c2) {
  int i1 = 0, i2 = 0;

  /*Cria o conjunto que posteriormente tem que receber free apos o uso para nao
   * ter leak*/
  struct conjunto *conj = criaConj();

  if (conj != NULL) {
    while (i1 < c1->tam && i2 < c2->tam) {
      if (c1->elementos[i1] < c2->elementos[i2]) {
        insereConj(conj, c1->elementos[i1]);
        i1++;
      } else if (c1->elementos[i1] > c2->elementos[i2]) {
        insereConj(conj, c2->elementos[i2]);
        i2++;
      } else {
        insereConj(conj, c1->elementos[i1]);
        i1++; /*pula para nao repetir numero*/
        i2++; /*pula para nao repetir numero*/
      }
    }

    /*Copie os elementos restantes do conjunto que nao terminou*/
    while (i1 < c1->tam) {
      insereConj(conj, c1->elementos[i1]);
      i1++;
    }

    while (i2 < c2->tam) {
      insereConj(conj, c2->elementos[i2]);
      i2++;
    }

    return conj;
  } else {
    /*Como usa a funcao insereConj caso aja falha de alocacao ira retornar
     * NULL*/
    return NULL;
  }
}

/*Se os valores sao iguas adiciona no conjunto, se forem diferentes, faz o
iterador que aponta para o menor numero andar uma 'casa' para frente, finaliza o
processo quando um dos iteradores chegar ao fim do conjunto */
struct conjunto *intersecao(struct conjunto *c1, struct conjunto *c2) {
  int i1 = 0, i2 = 0;

  /*Cria o conjunto que posteriormente tem que receber free apos o uso para nao
   * ter leak*/
  struct conjunto *conj = criaConj();

  if (conj != NULL) {
    while (i1 < c1->tam && i2 < c2->tam) {
      if (c1->elementos[i1] == c2->elementos[i2]) {
        insereConj(conj, c1->elementos[i1]);
        i1++;
        i2++;
      } else if (c1->elementos[i1] < c2->elementos[i2]) {
        i1++;
      } else {
        i2++;
      }
    }
    return conj;
  } else {
    /*Como usa a funcao insereConj caso aja falha de alocacao ira retornar
     * NULL*/
    return NULL;
  }
}

bool conjVazio(struct conjunto *c) {
  if (c->elementos == 0) {
    return true;
  };
  return false;
}

void imprimeConj(struct conjunto *c) {
  int i;
  for (i = 0; i < c->tam; i++)
    printf(" %d ", *(c->elementos + i));
  printf("\n");
}
