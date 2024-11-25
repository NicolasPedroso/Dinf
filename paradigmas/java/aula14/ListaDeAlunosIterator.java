import java.util.Iterator;
import java.util.List;

public class ListaDeAlunosIterator implements Iterator {
    private List alunos;
    private int posicao;

    public ListaDeAlunosIterator(List alunos) {
        this.alunos = alunos;
        this.posicao = 0;
    }

    public boolean hasNext() {
        return posicao < alunos.size();
    }

    public Aluno next() {
        if (!hasNext()) {
            throw new IllegalStateException("Não há mais alunos.");
        }
        return alunos.get(posicao++);
    }
}