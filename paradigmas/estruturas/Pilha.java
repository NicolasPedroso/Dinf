class Nodo {
    String elemento;
    Nodo proximo = null;

    public Nodo(String elemento) {
        this.elemento = elemento;
    }
}

public class Pilha {
    private Nodo topo = null;
    private String nome = "lista";

    // Método para empilhar um elemento na pilha
    public void push(String elemento) {
        Nodo no = new Nodo(elemento);
        no.proximo = this.topo;
        this.topo = no;
    }

    // Método para desempilhar o elemento do topo da pilha
    public void pop() {
        if (topo != null) {
            Nodo aux = this.topo;
            this.topo = aux.proximo;
            aux = null; // Remove a referência para ajudar o Garbage Collector
        } else {
            System.out.println("A pilha está vazia.");
        }
    }

    // Método para retornar o elemento do topo sem remover
    public String top() {
        if (topo != null) {
            return topo.elemento;
        } else {
            System.out.println("A pilha está vazia.");
            return null;
        }
    }

    // Método para verificar se a pilha está vazia
    public boolean empty() {
        return topo == null;
    }

    // Método para retornar o tamanho da pilha
    public int size() {
        int contador = 0;
        Nodo atual = topo;
        
        while (atual != null) {
            contador++;
            atual = atual.proximo;
        }
        
        return contador;
    }

    // Método para imprimir todos os elementos da pilha
    public void imprimePilha() {
        if (empty()) {
            System.out.println("A pilha está vazia.");
            return;
        }

        Nodo atual = topo;
        System.out.println("Elementos da pilha:");
        while (atual != null) {
            System.out.println(atual.elemento);
            atual = atual.proximo;
        }
    }

    // Método main para testar a pilha
    public static void main(String[] args) {
        Pilha pilha = new Pilha();
        Pilha p = new Pilha();

        for(int i = 0; i < 10; i++) {
            p.push("Elemento " + i);
        }

        pilha.push("Elemento 1");
        pilha.push("Elemento 2");
        pilha.push("Elemento 3");
        pilha.push("Elemento 4");
        pilha.push("Elemento 5");
        pilha.push("Elemento 6");
        pilha.push("Elemento 7");
        pilha.push("Elemento 8");
        pilha.push("Elemento 9");
        pilha.push("Elemento 10");

        while (!pilha.empty()) {
            pilha.pop();
        }

        System.out.println("Elemento do topo: " + pilha.top()); // Saída: Elemento 3
        System.out.println("Tamanho da pilha: " + pilha.size()); // Saída: 3

        pilha.imprimePilha();

        pilha.pop();
        System.out.println("\nDepois de um pop:");
        pilha.imprimePilha();
        p.imprimePilha();

        System.out.println("A pilha está vazia? " + pilha.empty()); // Saída: false
    }
}
