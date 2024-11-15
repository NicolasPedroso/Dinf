/*******************************************
 * Biblioteca para manipulação de redes
 * metabólicas.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "rede_metabolica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Cria grafo G e lê a rede metabólica do arquivo apontado por <f_met>,
// adicionando em G as reações, enzimas e metabólitos, com as respectivas conexões.
// Devolve o grafo G.
grafo le_rede_metabolica(FILE *f_met) {

    grafo G = cria_grafo(1);
    char linha[256];
    char *token;
    int id_vertice = 1;
    int id_aresta = 1;
    int produto = 0;

    vertice reacao = NULL;
    vertice metabolito = NULL;
    vertice enzima = NULL;

    while (fgets(linha, sizeof(linha), f_met) != NULL) {
        /*Usando strtok para dividir a linha em tokens*/
        token = strtok(linha, " ");
        produto = 0;
        while (token != NULL) {
            /*Verifica se eh reacao*/
            if (token[0] == 'R') {
                adiciona_vertice(id_vertice, token, REACAO, G);

                reacao = busca_chave_int(id_vertice, vertices(G), (int_f_obj)vertice_id);
                id_vertice++;
            }

            /*Verifica se eh metabolito*/
            if (token[0] == 'M') {
                metabolito = busca_chave_str(token, vertices(G), (str_f_obj)vertice_rotulo);
                /*Verifica se metabolito ainda nao existe se nao existir criara um novo*/
                if (metabolito == NULL) {
                    adiciona_vertice(id_vertice, token, METABOLITO, G);
                    id_vertice++;
                    metabolito = busca_chave_str(token, vertices(G), (str_f_obj)vertice_rotulo);
                }
                
                /*Verifica se metabolito esta eh um produto*/
                if (produto) {
                    adiciona_aresta(id_aresta, reacao->id, metabolito->id, G);
                    id_aresta++;
                } else {
                    adiciona_aresta(id_aresta, metabolito->id, reacao->id, G);
                    id_aresta++;
                }
            }
            
            /*Verifica se eh enzima*/
            if (token[0] == '_') {
                enzima = busca_chave_str(token, vertices(G), (str_f_obj)vertice_rotulo);

                if (enzima == NULL) {
                    adiciona_vertice(id_vertice, token, ENZIMA, G);
                    id_vertice++;
                    enzima = busca_chave_str(token, vertices(G), (str_f_obj)vertice_rotulo);
                }

                adiciona_aresta(id_aresta, enzima->id, reacao->id, G);
                id_aresta++;
            }
            if (token[0] == '=') produto++;
            token = strtok(NULL, " "); /*Obtem o proximo token*/
        }
    }

    return G;
}

// Cria lista L e lê da entrada padrão os substratos iniciais, adicionando
// em L os vértices que representam os substratos.
// Devolve a lista de vértices L.
lista le_substratos(grafo G) {

    lista L = cria_lista();

    char substrato[3];

    while (scanf("%3s", substrato) == 1) {
        if (!strcmp(substrato, "FIM") == 0) {
            vertice vertice = busca_chave_str(substrato, vertices(G), (str_f_obj)vertice_rotulo);
            empilha(vertice, L);
        }
    }

    //free(L); /*Resolve porem muito estranho o jeito*/

    return L;
}

// Função auxiliar que adiciona na rede metabólica uma reação falsa que gera
// todos os substratos iniciais (dado pela lista de vértices <substratos>).
// Deve adicionar um novo vértice com rótulo "SF" representando o substrato
// falso inicial e um novo vértice com rótulo "RF" representando a reação falsa.
// Deve também adicionar as arestas necessárias.
// ATENÇÃO: os rótulos "SF" e "RF" são usados no método imprime_reacoes_minimas().
void adiciona_reacao_falsa(lista substratos, grafo G) {

    int id_aresta = -1;

    adiciona_vertice(-1, "RF", REACAO, G);
    adiciona_vertice(-2, "SF", METABOLITO, G);

    vertice adiciona_reacao_falsa = busca_chave_str("RF", vertices(G), (str_f_obj)vertice_rotulo);

    vertice adiciona_substrato_falso = busca_chave_str("SF", vertices(G), (str_f_obj)vertice_rotulo);

    adiciona_aresta(id_aresta, adiciona_substrato_falso->id, adiciona_reacao_falsa->id, G);

    while (vazio(substratos) == 0) {
        id_aresta--;
        vertice substrato = desempilha(substratos);
        adiciona_aresta(id_aresta, adiciona_reacao_falsa->id, substrato->id, G);
    }
}

// Função auxiliar que inicializa os custos e pais dos vértices do grafo G para
// iniciar busca em largura. O custo de uma reação é a quantidade de enzimas que
// a cataliza.
// Devolve uma lista de vértices para ser a Fila inicial do algoritmo de busca.
lista inicializa_custos(grafo G) {
    lista F = cria_lista();
    
    /*Percorre todos os vertices atualizando custo e pai*/
    no no = primeiro_no(vertices(G));
    for (no; no; no = proximo(no)) {
        vertice vertice = conteudo(no);
        vertice->custo = INT_MAX;
        vertice->pai = NULL;
        
        /*Inicia custo 0*/
        if (!strcmp(vertice_rotulo(vertice), "SF")) vertice->custo = 0;

        /*Enzima nao precisam entra na fila pois custo sempre infinito*/
        if (vertice_particao(vertice) != ENZIMA) empilha(vertice, F);
    }

    return F;
}

/*Funcao auxiliar para saber a quantidade de enzimas da reacao*/
int enzimas_reacao(vertice v) {
    int enzimas = 0;
    
    /*Percorre a fronteira de entrada do vertice atualiza toda vez que encontra uma enzima*/
    no no = primeiro_no(fronteira_entrada(v));
    for (no; no; no = proximo(no)) {
        aresta aresta = conteudo(no);

        if (vertice_particao(aresta->u) == ENZIMA)
            enzimas++;
    }

    return enzimas;
}

// Algoritmo variante de Dijkstra que encontra o conjunto de reações de custo
// mínimo (número de enzimas) que produz todos os metabólitos da rede, considerando
// como substratos iniciais os metabólitos representados pelos vértices na lista
// substratos.
// Ao final do algoritmo, cada metabólito deve ter como pai (na estrutura vértice->pai)
// a reação "ótima" que o produz.
void processa(lista substratos, grafo G){

    // adiciona uma reação falsa para iniciar a busca
    adiciona_reacao_falsa(substratos, G);

    // inicializa custos, pais e fila inicial da busca F
    lista F = inicializa_custos(G);

    // variante do Algoritmo de Dijkstra para resolver o problema
    while (!vazio(F)) {
        int custo_atual = 0;
        vertice vertice = remove_min(F, (int_f_obj)custo);
        
        /*Verifica se vertice eh uma reacao pois reacoes terao custo igual a seu numero de enzimas*/
        /*atualiza o custo atual para guardar quantas enzimas foram usadas ate o momento*/
        if (vertice_particao(vertice) == REACAO) {
            vertice->custo = enzimas_reacao(vertice);
            custo_atual += custo(vertice);
        }
        
        no no = primeiro_no(fronteira_saida(vertice));
        for (no; no; no = proximo(no)) {
            aresta aresta = conteudo(no);
            /*Se o vizinho for um metabolito verifica se o custo_atual eh menor que seu custo se sim atualiza custo*/
            if (vertice_particao(aresta->v) == METABOLITO) {
                if (custo_atual < aresta->v->custo) {
                    aresta->v->custo = custo_atual;
                    aresta->v->pai = vertice;
                }
            }
            /*Se for uma reacao atualiza custo com o custo_atual mais o numero de enzimas da reacao*/
            else {
                aresta->v->custo = custo_atual + enzimas_reacao(aresta->v);
                aresta->v->pai = vertice;
            }
        }
    }

    free(F);
}

// Imprime resultados com base nos pais dos vértices (na estrutura vértice->pai),
// calculados pelo método processa().
void imprime_reacoes_minimas(grafo G) {
  
    // Para cada metabólito, imprime as reações "ótimas"
    for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
        vertice v = conteudo(n);
        if (vertice_particao(v) == METABOLITO && pai(v)) {
            printf("%s: ", vertice_rotulo(v));
      
            // cria lista de reações necessárias para sua produção
            lista R = cria_lista();
            empilha(pai(v), R);
      
            // seta todas as reações como ABERTOS, para não repetir
        for (no p = primeiro_no(vertices(G)); p; p = proximo(p)) {
            vertice w = conteudo(p);
            if (vertice_particao(w) == REACAO)
                w->estado = ABERTO;
        }
      
        // Enquanto tiver reações ainda não processadas, imprime
        while (!vazio(R)) {
            vertice w = desempilha(R);
            if (estado(w) == ABERTO && strcmp(vertice_rotulo(w), "RF")) { // não inclui a reação falsa
                printf("%s ", vertice_rotulo(w));
                w->estado = FECHADO;
          
                // coloca na lista as reações antecessoras
                for (no p = primeiro_no(fronteira_entrada(w)); p; p = proximo(p)) {
                    aresta e = conteudo(p);
                    vertice u = vertice_u(e);
                    if (vertice_particao(u) == METABOLITO && pai(u))
                        empilha(pai(u), R);
                }
            }
        }
      printf("\n");
      free(R);
    }
  }
}