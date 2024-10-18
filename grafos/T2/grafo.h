/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _GRAFO_
#define _GRAFO_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct t_atomo *atomo;
typedef struct t_ligacao *ligacao;
typedef struct t_grafo *grafo;

typedef struct t_atomo {
	int id;
	char elemento;
	lista fronteira;
} t_atomo;

typedef struct t_ligacao {
	int id;
	int tipo;
	atomo u, v;
} t_ligacao;

typedef struct t_grafo {
  lista atomos;
  lista ligacoes;
} t_grafo ;

//---------------------------------------------------------
// getters:

int atomo_id(atomo v);
lista fronteira(atomo v);
int ligacao_id(ligacao e);
atomo atomo_u(aresta e);
atomo atomo_v(aresta e);
lista atomos(grafo G);
lista ligacoes(grafo G);

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo();

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G);

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_atomo(int id, char elemento, grafo G);

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_atomo(int id, grafo G);

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_ligacoes(int id, int tipo, int u_id, int v_id, grafo G);

// remove aresta com id <id> do grafo G e a destroi
void remove_ligacao(int id, int tipo, grafo G); // não pode fazer ponterado

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(atomo v);

// imprime o grafo G
void imprime_grafo(grafo G);

// imprime o vertice v
void imprime_atomo(atomo v);

// imprime a aresta e
void imprime_ligacao(ligacao e);

#endif
