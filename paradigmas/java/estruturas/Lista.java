public class Lista {
    private class Nodo {
        String elemento;
        Nodo proximo = null;
        Nodo anterior = null; // Ponteiro para o nodo anterior

        public Nodo(String elemento) {
            this.elemento = elemento;
        }
    }

    private Nodo comeco = null;
    private Nodo fim = null; // Ponteiro para o último nodo
    String nome = "lista";

    // Método para inserir um elemento na lista em uma posição específica
    public void insert(String elemento, int pos) {
        Nodo novoNodo = new Nodo(elemento);

        if (pos <= 1) {
            // Insere no começo
            novoNodo.proximo = comeco;
            if (comeco != null) {
                comeco.anterior = novoNodo; // Atualiza o anterior do nodo atual
            } else {
                fim = novoNodo; // Se a lista estava vazia, o novo nodo é também o fim
            }
            comeco = novoNodo;
        } else {
            Nodo aux = comeco;
            int i = 1;
            while (aux != null && i < pos - 1) {
                aux = aux.proximo;
                i++;
            }

            if (aux == null) {
                // Se a posição é maior que o número de elementos, insere no final
                novoNodo.anterior = fim;
                if (fim != null) {
                    fim.proximo = novoNodo;
                }
                fim = novoNodo; // Atualiza o fim
            } else {
                // Insere no meio da lista
                novoNodo.proximo = aux.proximo;
                novoNodo.anterior = aux;
                if (aux.proximo != null) {
                    aux.proximo.anterior = novoNodo; // Atualiza o anterior do próximo nodo
                } else {
                    fim = novoNodo; // Atualiza o fim se inserido no final
                }
                aux.proximo = novoNodo;
            }
        }
    }

    // Método para remover um elemento da lista em uma posição específica
    public void remove(int pos) {
        if (comeco == null) return; // Lista vazia, não há o que remover

        Nodo aux = comeco;

        if (pos == 1) {
            // Remove o primeiro elemento
            comeco = aux.proximo;
            if (comeco != null) {
                comeco.anterior = null; // Atualiza o anterior do novo começo
            } else {
                fim = null; // Se a lista ficou vazia, atualiza o fim também
            }
            aux = null; // Para ajudar o Garbage Collector
            return;
        }

        int i = 1;
        while (aux != null && i < pos) {
            aux = aux.proximo;
            i++;
        }

        if (aux == null) return; // Verifica se a posição é válida

        if (aux.anterior != null) {
            aux.anterior.proximo = aux.proximo; // Atualiza o próximo do nodo anterior
        }
        if (aux.proximo != null) {
            aux.proximo.anterior = aux.anterior; // Atualiza o anterior do próximo nodo
        } else {
            fim = aux.anterior; // Atualiza o fim se o último nodo foi removido
        }
        aux = null; // Para ajudar o Garbage Collector
    }

    // Método para retornar o número de elementos na lista
    public int size() {
        int count = 0;
        Nodo aux = comeco;
        while (aux != null) {
            count++;
            aux = aux.proximo;
        }
        return count;
    }

    // Método para verificar se a lista está vazia
    public boolean empty() {
        return comeco == null;
    }

    // Método para imprimir todos os elementos da lista
    public void imprimeLista() {
        Nodo aux = comeco;
        while (aux != null) {
            System.out.print(aux.elemento + " ");
            aux = aux.proximo;
        }
        System.out.println(); // Nova linha ao final da impressão
    }

    public static void main(String[] args) {
        Lista lista = new Lista();

        // Inserindo elementos na lista
        for (int j = 1; j <= 10; j++) {
            lista.insert("Elemento " + j, j);
        }

        // Exibindo a lista
        System.out.println("Lista após inserção:");
        lista.imprimeLista(); // Deve imprimir "Elemento 1 Elemento 2 Elemento 3 ... Elemento 10"
        
        // Testando a remoção
        lista.remove(5); // Remove "Elemento 5"
        System.out.println("Lista após remover o 5º elemento:");
        lista.imprimeLista(); // Deve imprimir "Elemento 1 Elemento 2 Elemento 3 Elemento 4 Elemento 6 Elemento 7 Elemento 8 Elemento 9 Elemento 10"

        // Verificando se a lista está vazia
        System.out.println("A lista está vazia? " + lista.empty()); // Deve retornar false

        // Removendo todos os elementos
        for (int j = 1; j <= 9; j++) {
            lista.remove(1); // Remove sempre o primeiro elemento
        }
        
        // Removendo o último elemento
        lista.remove(1); // Remove "Elemento 10"
        
        // Verificando se a lista está vazia novamente
        System.out.println("A lista está vazia? " + lista.empty()); // Deve retornar true
    }
}
