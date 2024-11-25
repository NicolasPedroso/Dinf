import java.util.*;

class Main {
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);
        ArrayList<Aluno> alunos = new ArrayList<>();

        System.out.println("Digite o número de alunos a ser criados");
        int valor = teclado.nextInt();
        teclado.nextLine();  // Consumir o newline após nextInt

        for (int i = 0; i < valor; i++) {
            Aluno aluno = new Aluno();

            System.out.println("Digite um nome");
            String nomeAluno = teclado.nextLine();
            aluno.setNome(nomeAluno);

            System.out.println("Digite um endereço");
            String enderecoAluno = teclado.nextLine();
            aluno.setEndereco(enderecoAluno);

            System.out.println("Digite um email");
            String emailAluno = teclado.nextLine();
            aluno.setEmail(emailAluno);

            System.out.println("Digite um telefone");
            String telefoneAluno = teclado.nextLine();
            aluno.setTelefone(telefoneAluno);

            for (int j = 0; j < 4; j++) {
                System.out.println("Digite a nota do aluno");
                int notaAluno = teclado.nextInt();
                aluno.setNota(j, notaAluno);
            }
            teclado.nextLine();  // Consumir o newline após a última nota
            
            // Adiciona o aluno à lista
            alunos.add(aluno);
        }

        teclado.close();

        // Imprime todos os alunos criados
        System.out.println("\nAlunos cadastrados:");
        for (Aluno aluno : alunos) {
            System.out.println(aluno.getNome());
            System.out.println(aluno.getEndereco());
            System.out.println(aluno.getEmail());
            System.out.println(aluno.getTelefone());
            int media = 0;
            for( int nota = 0; nota < 4; nota++){
                media += aluno.getNota(nota);
            }            
            System.out.println("Média do aluno: " + (media/4));
        }
    }
}
