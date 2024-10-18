/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;  // mudar para o nome do atomo
};
lista fronteira(vertice v) {
  return v->fronteira; // nomear os atomos da fronteira
};
int aresta_id(aresta e) {
  return e->id; // mudar para o tipo de ligação
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->atomos = cria_lista();
  G->ligacoes = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  
  /*Passa por todos os vertices de G removendo*/
  /*Assim também passando por todas as arestas de G as removendo*/
  for(atomo atomos_In_G = topo(atomos(G)); !vazio(atomos(G)); atomos_In_G = topo(atomos(G)))
  {
    remove_atomo(atomo_id(atomos_In_G), G);
  }
  free(ligacoess(G));
  free(atomos(G));
  free(G);

  return;
}

// cria novo vertice com id <id> e adiciona ao grafo G
// mudar para criaLigacao e que faz um for com o tipo de ligacao
void adiciona_atomo(int id, char tipo, grafo G) {
  
  atomo novo_atomo =(atomo) malloc(sizeof(t_atomo));
  if(!novo_atomo) exit(_ERRO_MALLOC_);

  novo_atomo->id = id;
  novo_atomo->tipo = tipo;
  novo_vertice->fronteira = cria_lista();
  empilha(novo_vertice, G->vertices);
  
  return;
}

// remove vertice com id <id> do grafo G e o destroi
// deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  atomo v = busca_chave(id, atomos(G), (int_f_obj)atomo_id);
  
  if (!v) return;

  /*Remove arestas incidentes ao vertice e as destroi*/
  while (!vazio(fronteira(v))) {
    ligacao e = topo(fronteira(v));
    remove_ligacao(ligacao_id(e), G);
  }

  /*Remove o vertice da lista de vertices do grafo e o destroi*/
  remove_chave(id, atomos(G), (int_f_obj)atomo_id);
  free(fronteira(v));
  free(v);

  return;
}

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_ligacoes(int id, int tipo, int u_id, int v_id, grafo G) {
  vertice u = busca_chave(u_id, vertices(G), (int_f_obj)vertice_id);
  vertice v = busca_chave(v_id, vertices(G), (int_f_obj)vertice_id);


  /*Sai da funcao se o vertice u ou v nao existir*/
  if (!u) {
    fprintf(stderr, "Erro: Vertice %d não existe no grafo.\n", u_id);
    return;
  }
  if (!v) {
    fprintf(stderr, "Erro: Vertice %d não existe no grafo.\n", v_id);
    return;
  }

  for(int i = 0, i < tipo, i++) {
    ligacao novo_ligacao =(ligacao) malloc(sizeof(t_ligacao));
    if(!novo_ligacao)
      exit(_ERRO_MALLOC_);

    novo_ligacao->id = id;
    novo_ligacao->u = u;
    novo_ligacao->v = v;
  
    empilha(novo_ligacao, fronteira(atomo_u(novo_ligacao)));
    empilha(novo_ligacao, fronteira(atomo_v(novo_ligacao)));
    empilha(novo_ligacao, ligacoes(G));

  }
  
  return;
}

// remove aresta com id <id> do grafo G e a destroi
void remove_ligacao(int id, grafo G) {
  
  ligacao l = remove_chave( id, ligacoes(G),(int_f_obj) ligacao_id);

  remove_chave( ligacao_id(l), fronteira(atomo_u(l)),(int_f_obj)ligacao_id);
  remove_chave( ligacao_id(l), fronteira(atomo_v(l)),(int_f_obj)ligacao_id);

  free(l);
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(atomos(G), (void_f_obj)imprime_atomo);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(ligacoes(G), (void_f_obj)imprime_ligacao);
  printf("\n");
}

// imprime o vertice v
void imprime_atomo(atomo v) {
  printf("<%d> - [%d]( ", atomo_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj)imprime_ligacao);
  printf(") | ");
}

// imprime a aresta e
void imprime_ligacao(ligacao e) {
  int u_id = ligacao_id(ligacao_u(e));
  int v_id = ligacao_id(ligacao_v(e));
  printf("<%d>:{%d,%d}", ligacao_id(e), u_id, v_id);
}