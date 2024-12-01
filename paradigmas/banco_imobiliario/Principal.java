import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Principal {
    static List<Jogadores> jogadores = new ArrayList<>();
    private static final String ARQUIVO = "jogadores.save";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int opcao;

        do {
            System.out.println("\n1. Adicionar Pessoa");
            System.out.println("2. Listar Pessoas");
            System.out.println("3. Atualizar Pessoa");
            System.out.println("4. Remover Pessoa");
            System.out.println("5. Salvar em Arquivo");
            System.out.println("6. Carregar de Arquivo");
            System.out.println("7. Sair");
            System.out.print("Escolha uma opção: ");
            opcao = scanner.nextInt();
            scanner.nextLine(); // Consumir nova linha

            switch (opcao) {
                case 1 -> adicionarPessoa(scanner);
                case 2 -> listarPessoas();
                case 3 -> atualizarPessoa(scanner);
                case 4 -> removerPessoa(scanner);
                case 5 -> salvarEmArquivo();
                case 6 -> carregarDeArquivo();
                case 7 -> System.out.println("Saindo...");
                default -> System.out.println("Opção inválida.");
            }
        } while (opcao != 7);

        scanner.close();
    }

    // Adicionar uma nova pessoa
    public static void adicionarPessoa(Scanner scanner) {
        System.out.print("Tipo de pessoa (Aluno, Professor, Tecnico): ");
        String tipo = scanner.nextLine();

        System.out.print("Nome: ");
        String nome = scanner.nextLine();

        System.out.print("Email: ");
        String email = scanner.nextLine();

        Pessoa pessoa = switch (tipo.toLowerCase()) {
            case "aluno" -> new Aluno(nome, email);
            case "professor" -> new Professor(nome, email);
            case "tecnico" -> new TecnicoAdministrativo(nome, email);
            default -> null;
        };

        if (pessoa != null) {
            pessoas.add(pessoa);
            System.out.println("Pessoa adicionada com sucesso!");
        } else {
            System.out.println("Tipo inválido.");
        }
    }

    // Listar todas as pessoas cadastradas
    public static void listarPessoas() {
        if (pessoas.isEmpty()) {
            System.out.println("Nenhuma pessoa cadastrada.");
        } else {
            pessoas.forEach(System.out::println);
        }
    }

    // Atualizar dados de uma pessoa
    public static void atualizarPessoa(Scanner scanner) {
        System.out.print("Digite o nome da pessoa a ser atualizada: ");
        String nome = scanner.nextLine();

        Pessoa pessoa = buscarPessoaPorNome(nome);

        if (pessoa != null) {
            System.out.print("Novo nome: ");
            String novoNome = scanner.nextLine();
            System.out.print("Novo email: ");
            String novoEmail = scanner.nextLine();

            pessoa.setNome(novoNome);
            pessoa.setEmail(novoEmail);

            System.out.println("Dados atualizados com sucesso!");
        } else {
            System.out.println("Pessoa não encontrada.");
        }
    }

    // Remover uma pessoa
    public static void removerPessoa(Scanner scanner) {
        System.out.print("Digite o nome da pessoa a ser removida: ");
        String nome = scanner.nextLine();

        Pessoa pessoa = buscarPessoaPorNome(nome);

        if (pessoa != null) {
            pessoas.remove(pessoa);
            System.out.println("Pessoa removida com sucesso!");
        } else {
            System.out.println("Pessoa não encontrada.");
        }
    }

    // Buscar uma pessoa pelo nome
    public static Pessoa buscarPessoaPorNome(String nome) {
        for (Pessoa pessoa : pessoas) {
            if (pessoa.getNome().equalsIgnoreCase(nome)) {
                return pessoa;
            }
        }
        return null;
    }

    // Salvar a lista de pessoas em arquivo
    public static void salvarEmArquivo() {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(ARQUIVO))) {
            for (Pessoa pessoa : pessoas) {
                writer.write(pessoa.toString() + "\n");
            }
            System.out.println("Pessoas salvas no arquivo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao salvar o arquivo.");
            e.printStackTrace();
        }
    }

    // Carregar a lista de pessoas do arquivo
    public static void carregarDeArquivo() {
        try (BufferedReader reader = new BufferedReader(new FileReader(ARQUIVO))) {
            pessoas.clear(); // Limpa a lista antes de carregar novos dados
            String linha;

            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split(" -> ");
                if (partes.length == 2) {
                    String tipo = partes[0].trim();
                    String[] dados = partes[1].split(", ");
                    String nome = dados[0].split(": ")[1];
                    String email = dados[1].split(": ")[1];

                    Pessoa pessoa = switch (tipo.toLowerCase()) {
                        case "aluno" -> new Aluno(nome, email);
                        case "professor" -> new Professor(nome, email);
                        case "técnico administrativo" -> new TecnicoAdministrativo(nome, email);
                        default -> null;
                    };

                    if (pessoa != null) {
                        pessoas.add(pessoa);
                    }
                }
            }

            System.out.println("Pessoas carregadas do arquivo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao carregar o arquivo.");
            e.printStackTrace();
        }
    }
}

// Classe base Pessoa
abstract class Pessoa {
    protected String nome;
    protected String email;

    public Pessoa(String nome, String email) {
        this.nome = nome;
        this.email = email;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        return "Nome: " + nome + ", Email: " + email;
    }
}

// Subclasse Aluno
class Aluno extends Pessoa {
    public Aluno(String nome, String email) {
        super(nome, email);
    }

    @Override
    public String toString() {
        return "Aluno -> " + super.toString();
    }
}

// Subclasse Professor
class Professor extends Pessoa {
    public Professor(String nome, String email) {
        super(nome, email);
    }

    @Override
    public String toString() {
        return "Professor -> " + super.toString();
    }
}

// Subclasse TecnicoAdministrativo
class TecnicoAdministrativo extends Pessoa {
    public TecnicoAdministrativo(String nome, String email) {
        super(nome, email);
    }

    @Override
    public String toString() {
        return "Técnico Administrativo -> " + super.toString();
    }
}
/*import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Principal {
    static List<Propriedade> propriedades = new ArrayList<>();
    private static final String ARQUIVO = "propriedades.save";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int opcao;

        do {
            System.out.println("\n1. Adicionar Propriedade");
            System.out.println("2. Listar Propriedades");
            System.out.println("3. Atualizar Propriedade");
            System.out.println("4. Remover Propriedade");
            System.out.println("5. Salvar em Arquivo");
            System.out.println("6. Carregar de Arquivo");
            System.out.println("7. Sair");
            System.out.print("Escolha uma opção: ");
            opcao = scanner.nextInt();
            scanner.nextLine(); // Consumir nova linha

            switch (opcao) {
                case 2 -> CartaPropriedade.listarPropriedades(propriedades);
                case 5 -> CartaPropriedade.salvarEmArquivo(propriedades, ARQUIVO);
                case 6 -> propriedades = CartaPropriedade.carregarDeArquivo(ARQUIVO);
                case 7 -> System.out.println("Saindo...");
                default -> System.out.println("Opção inválida.");
            }
        } while (opcao != 7);

        scanner.close();
    }
}
 */

 -------------------------------------------
 /*import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Principal {
    static List<Carta> cartas = new ArrayList<>();
    private static final String ARQUIVO = "sorteAzar.save";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int opcao;

        do {
            System.out.println("\n1. Adicionar sorteAzar");
            System.out.println("2. Listar cartas");
            System.out.println("3. Atualizar sorteAzar");
            System.out.println("4. Remover sorteAzar");
            System.out.println("5. Salvar em Arquivo");
            System.out.println("6. Carregar de Arquivo");
            System.out.println("7. Sair");
            System.out.print("Escolha uma opção: ");
            opcao = scanner.nextInt();
            scanner.nextLine(); // Consumir nova linha

            switch (opcao) {
                case 1 -> Carta.adicionarSorteAzar(cartas, scanner);
                case 2 -> Carta.listarCartas(cartas);
                case 3 -> Carta.atualizarSorteAzar(cartas, scanner);
                case 4 -> Carta.removerSorteAzar(cartas, scanner);
                case 5 -> Carta.salvarEmArquivo(cartas, ARQUIVO);
                case 6 -> cartas = Carta.carregarDeArquivo(ARQUIVO);
                case 7 -> System.out.println("Saindo...");
                default -> System.out.println("Opção inválida.");
            }
        } while (opcao != 7);

        scanner.close();
    }
}
 */