import java.util.ArrayList;
import java.util.List;

public class ListaDeAlunos {
    private static ListaDeAlunos instanciaUnica;
    private List<Aluno> alunos;  

    private ListaDeAlunos() {
        alunos = new ArrayList<>();
    }

    public static synchronazide Singleton ListaDeAlunos getInstancia()  {
        if (instanciaUnica == null) {
            instanciaUnica = new Singleton();
        }
        return instanciaUnica;
    }

    public void insere(Aluno aluno) {
        alunos.add(aluno);
    }

    public boolean vazia() {
        return alunos.isEmpty();
    }

    public int tamanho() {
        return alunos.size();
    }
}