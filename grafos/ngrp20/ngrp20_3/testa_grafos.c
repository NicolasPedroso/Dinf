/*******************************************
 * Leitura e impressao de grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
  
  // cria grafo vazio
  grafo G = cria_grafo();
  
  // le n e adiciona vertices 1..n
  int n;
  scanf("%d", &n); // qtd vertices
  
  for (int i = 1; i <= n; ++i)
    adiciona_vertice(i, G);
  
  // le pares u v e adiciona arestas {u,v}
  // termina quando digitar 0 0
  int id = 1;
  int u, v;
  scanf("%d %d", &u, &v);
  while (u && v) {
    adiciona_aresta(id, u, v, G);
    ++id;
    scanf("%d %d", &u, &v);
  }
  
  // imprime informacoes do grafo
  imprime_grafo(G);

  /*cria lista de ID's validos do grafo G*/
  lista conjunto_X = ler_conjunto_vertices(G);

  /*Cria subgrafo do grafo G usando a lista da funcao acima*/
  grafo G_subconjunto = cria_subgrafo(conjunto_X, G);

  /*imprime informacoes do subgrafo*/
  imprime_grafo(G_subconjunto);

  /*Libera a memoria das estrutuas usadas*/
  destroi_grafo(G_subconjunto);
  destroi_grafo(G); 
  while (!vazio(conjunto_X)) {
    int* id = (int*)desempilha(conjunto_X); /*Desempilha o id*/
    free(id);
  }
  free(conjunto_X); /*Libera a lista em si*/

  return 0;
}
