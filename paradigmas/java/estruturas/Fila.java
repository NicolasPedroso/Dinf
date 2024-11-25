public class Fila {
    private class Nodo {
        String elemento;
        Nodo proximo;

        public Nodo(String elemento) {
            this.elemento = elemento;
            this.proximo = null;
        }
    }

    private Nodo inicio = null;
    private Nodo fim = null;
    private int tamanho = 0;
    String nome = "fila";

    // Método para adicionar um elemento na fila
    public void enqueue(String elemento) {
        Nodo no = new Nodo(elemento);

        if (inicio == null) {
            // Se a fila estiver vazia
            inicio = no;
            fim = no;
        } else {
            // Adiciona o novo nodo no final
            fim.proximo = no;
            fim = no;
        }
        tamanho++;
    }

    // Método para remover um elemento da fila
    public void dequeue() {
        if (inicio != null) {
            Nodo aux = inicio;
            inicio = inicio.proximo; // Atualiza o início da fila
            aux = null; // Ajuda o Garbage Collector
            tamanho--;

            if (inicio == null) {
                // Se a fila ficou vazia, também atualiza o fim
                fim = null;
            }
        }
    }

    // Método para retornar o número de elementos na fila
    public int size() {
        return tamanho;
    }

    // Método para verificar se a fila está vazia
    public boolean empty() {
        return inicio == null;
    }

    // Método para imprimir todos os elementos da fila
    public void imprimeFila() {
        Nodo aux = inicio;
        while (aux != null) {
            System.out.print(aux.elemento + " ");
            aux = aux.proximo;
        }
        System.out.println(); // Nova linha ao final da impressão
    }

    public static void main(String[] args) {
        Fila fila = new Fila();

        // Adicionando elementos na fila
        fila.enqueue("Elemento 1");
        fila.enqueue("Elemento 2");
        fila.enqueue("Elemento 3");

        System.out.println("Elementos na fila:");
        fila.imprimeFila(); // Deve imprimir "Elemento 1 Elemento 2 Elemento 3"

        System.out.println("Tamanho da fila: " + fila.size()); // Deve retornar 3

        // Removendo um elemento da fila
        fila.dequeue();
        System.out.println("Elementos na fila após uma remoção:");
        fila.imprimeFila(); // Deve imprimir "Elemento 2 Elemento 3"

        System.out.println("A fila está vazia? " + fila.empty()); // Deve retornar false

        // Removendo todos os elementos
        fila.dequeue(); // Remove "Elemento 2"
        fila.dequeue(); // Remove "Elemento 3"

        System.out.println("A fila está vazia? " + fila.empty()); // Deve retornar true
    }
}
