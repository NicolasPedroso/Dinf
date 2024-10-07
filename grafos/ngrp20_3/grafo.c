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
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
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
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  
  /*Passa por todos os vertices de G removendo*/
  /*Assim também passando por todas as arestas de G as removendo*/
  for(vertice vertices_In_G = topo(vertices(G)); !vazio(vertices(G)); vertices_In_G = topo(vertices(G)))
  {
    remove_vertice(vertice_id(vertices_In_G), G);
  }
  free(arestas(G));
  free(vertices(G));
  free(G);

  return;
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {
  
  vertice novo_vertice =(vertice) malloc(sizeof(t_vertice));
  if(!novo_vertice) exit(_ERRO_MALLOC_);

  novo_vertice->id = id;
  novo_vertice->fronteira = cria_lista();
  empilha(novo_vertice, G->vertices);
  
  return;
}

// remove vertice com id <id> do grafo G e o destroi
// deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  vertice v = busca_chave(id, vertices(G), (int_f_obj)vertice_id);
  
  if (!v) return;

  /*Remove arestas incidentes ao vertice e as destroi*/
  while (!vazio(fronteira(v))) {
    aresta e = topo(fronteira(v));
    remove_aresta(aresta_id(e), G);
  }

  /*Remove o vertice da lista de vertices do grafo e o destroi*/
  remove_chave(id, vertices(G), (int_f_obj)vertice_id);
  free(fronteira(v));
  free(v);

  return;
}

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
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


  aresta novo_aresta =(aresta) malloc(sizeof(t_aresta));
  if(!novo_aresta)
    exit(_ERRO_MALLOC_);

  novo_aresta->id = id;
  novo_aresta->u = u;
  novo_aresta->v = v;

  empilha(novo_aresta, fronteira(vertice_u(novo_aresta)));
  empilha(novo_aresta, fronteira(vertice_v(novo_aresta)));
  empilha(novo_aresta, arestas(G));

  return;
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  
  aresta a = remove_chave( id, arestas(G),(int_f_obj) aresta_id);

  remove_chave( aresta_id(a), fronteira(vertice_u(a)),(int_f_obj)aresta_id);
  remove_chave( aresta_id(a), fronteira(vertice_v(a)),(int_f_obj)aresta_id);

  free(a);
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
  imprime_lista(vertices(G), (void_f_obj)imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj)imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("<%d> - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj)imprime_aresta);
  printf(") | ");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("<%d>:{%d,%d}", aresta_id(e), u_id, v_id);
}

/*Funcao para criar um grafo G[X] baseado numa lista de vertices*/
grafo cria_subgrafo(lista conjunto_X, grafo G) {
    grafo G_sub = cria_grafo();
    
    /*Adiciona os vertices do conjunto X ao grafo G_sub*/
    for (no n = primeiro_no(conjunto_X); n != NULL; n = proximo(n)) {
        int vertice_id = *(int*)(n->conteudo);
        adiciona_vertice(vertice_id, G_sub);
    }

    /*Adiciona as arestas que conectam os vertices presentes no subconjunto G_sub*/
    for (no n = G->arestas->primeiro_no; n != NULL; n = proximo(n)) {
        aresta a = (aresta)n->conteudo;
        
        int u_presente = 0, v_presente = 0;

        /*Verifica se o vertice u esta no subconjunto X*/
        for (no m = conjunto_X->primeiro_no; m != NULL; m = proximo(m)) {
            int vertice_id = *(int*)(m->conteudo);
            if (a->u->id == vertice_id) u_presente = 1;
            if (a->v->id == vertice_id) v_presente = 1;
        }

        /*Se ambos os vertices estiverem em X adiciona a aresta ao grafo G_sub*/
        if (u_presente && v_presente) {
            adiciona_aresta(a->id, a->u->id, a->v->id, G_sub);
        }
    }

    return G_sub;
}
/*Cria uma lista lendo uma sequencia de ID's e verifica se existe no Grafo G*/ 
lista ler_conjunto_vertices(grafo G) {
    lista conjunto_X = cria_lista();
    int id;
    printf("Insira os ids dos vértices (digite 0 para parar):\n");
    while (1) {
        scanf("%d", &id);
        if (id == 0) break;
        
        // Verifica se o vertice existe no grafo
        if (!busca_chave(id, vertices(G), (int_f_obj)vertice_id)) {
            printf("Vértice %d inexistente no grafo.\n", id);
        } else {
            int* novo_id = (int*)malloc(sizeof(int));
            if (!novo_id) {
                fprintf(stderr, "Erro: Falha ao alocar memória para novo ID.\n");
                exit(_ERRO_MALLOC_);
            }
            *novo_id = id;
            empilha(novo_id, conjunto_X);
        }
    }
    return conjunto_X;
}