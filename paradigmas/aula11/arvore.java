public class Arvore{
    private Nodo raiz;

    public Nodo getRaiz() {
        return raiz;
    }

    public void setRaiz() { 
        this.raiz = raiz;
    }

    public Arvore() {
        this.raiz = null;
    }

    public void insere(int elem) {
        if (this.raiz == null) {
            this.raiz = new Nodo (null, null, elem);
            System.out.println("Inseriu");
        }
        else {
            raiz = insereR(elem, this.raiz);
        }
    }

    public Nodo insereR(int elem, Nodo p) {
        if(p == null) {
            p = new Nodo (null, null, elem);
            System.out.println("Inseriu " + elem);
        }
    }
}