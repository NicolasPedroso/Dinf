struct conjunto {
  int tam;        /* tamanho usado ate maxTam */
  int maxTam;     /* tamanho maximo do vetor atualmente alocado */
  int *elementos; /* vetor de inteiros com no maximo maxTam elementos */
};

/* funcoes internas */
/* Funcao de busca para facilitar as funcoes dos conjuntos */
int buscaBinaria(struct conjunto *c, int x);

/* Funcao de aleatoridade em vetor */
void vetorAlet(int v[], int min, int max, int elementos);

/* funcoes internas */

/* Cria conjunto com tamanho max*/
struct conjunto *criaConj();

/* Remove todos os elementos do conjunto, libera espaco e devolve NULL*/
void destroiConj(struct conjunto *c);

/* Retorna verdadeito(true) se o conjunto esta vazio, caso contrario
 * falso(false) */
bool conjVazio(struct conjunto *c);

/* Retorna o tamanho do conjunto */
int tamConj(struct conjunto *c);

/* Insere o elemento x ao conjunto C, caso x nao exista em C */
/* Retorna verdadeiro(true) se inserir e falso(false) caso contrario */
bool insereConj(struct conjunto *c, int x);

/* Remove o elemento x ao conjunto C */
/* Retorna verdadeiro(true) se remover e falso(false) caso contrario */
bool removeConj(struct conjunto *c, int x);

/* Verifica se o elemento x pertence ao conjunto C */
/* Retorna verdadeiro(true) se pertence e falso(false) caso contrario*/
bool pertenceConj(struct conjunto *c, int x);

/* Retorna conjunto de tamanho alocado maximo tamConj(c1) + tamConj(c2) */
struct conjunto *uniao(struct conjunto *c1, struct conjunto *c2);

/* Retorna conjunto contendo valor que pertence aos dois conjuntos */
struct conjunto *intersecao(struct conjunto *c1, struct conjunto *c2);

/* Imprime o conjunto */
void imprimeConj(struct conjunto *c);