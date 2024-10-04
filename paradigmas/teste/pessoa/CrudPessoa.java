import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Frame extends JFrame implements ActionListener {
    static List<Pessoa> pessoas = new ArrayList<>();

    private JButton Badicionar, Blistar, Batualizar, Bremover, Bsalvar, Bcarregar, Bcancelar;
    private JTextField Tnome, Temail, Ttipo;
    private JLabel Lnome, Lemail, Ltipo, Lvazio;

    public Frame() {
        Badicionar = new JButton("Adicionar"); 
        Blistar = new JButton("Listar");
        Batualizar = new JButton("Atualizar"); 
        Bremover = new JButton("Remover");
        Bsalvar = new JButton("Salvar");
        Bcarregar = new JButton("Carregar");
        Bcancelar = new JButton("Cancelar");
        Badicionar.addActionListener(this); 
        Blistar.addActionListener(this);
        Batualizar.addActionListener(this); 
        Bremover.addActionListener(this);
        Bsalvar.addActionListener(this);
        Bcarregar.addActionListener(this);
        Bcancelar.addActionListener(this);
        
        Tnome = new JTextField("Nome");
        Temail = new JTextField("E-mail");
        Ttipo = new JTextField("Tipo");
        Lvazio = new JLabel(" ");

        this.getContentPane().setLayout(new GridLayout(8,1));
        this.getContentPane().add(Tnome);
        this.getContentPane().add(Temail);
        this.getContentPane().add(Ttipo);
        this.getContentPane().add(Lvazio);
        
        this.getContentPane().add(Badicionar);
        this.getContentPane().add(Blistar);
        this.getContentPane().add(Batualizar);
        this.getContentPane().add(Bremover);
        this.getContentPane().add(Bsalvar);
        this.getContentPane().add(Bcarregar);
        this.getContentPane().add(Bcancelar);

        this.getContentPane().add(Bsalvar);
        this.getContentPane().add(Bcancelar);
        this.setLocation(200,200);
        this.setSize(300,300);
    }

    public void actionPerformed(ActionEvent e) {
        //aqui vai o código para tratar os eventos dos botôes
        if (e.getSource() == Bsalvar) {
            System.out.println("voce tentou salvar");
        }
        if (e.getSource() == Bcancelar) {
            System.out.println("voce tentou cancelar");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        JFrame janela = new Frame();
        janela.show();
        WindowListener x = new WindowAdapter () {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        };
        janela.addWindowListener(x);

        int opcao;
        do {
            System.out.println("\n1. Adicionar Pessoa");
            System.out.println("2. Listar Pessoas");
            System.out.println("3. Atualizar Pessoa");
            System.out.println("4. Remover Pessoa");
            System.out.println("5. Salvar em arquivo criptografado");
            System.out.println("6. Carregar do arquivo criptografado");
            System.out.println("7. Sair");
            opcao = scanner.nextInt();
            scanner.nextLine();  // Consumir nova linha

            switch (opcao) {
                case 1:
                    adicionarPessoa(scanner);
                    break;
                case 2:
                    listarPessoas();
                    break;
                case 3:
                    atualizarPessoa(scanner);
                    break;
                case 4:
                    removerPessoa(scanner);
                    break;
                case 5:
                    salvarEmArquivoCriptografado();
                    break;
                case 6:
                    carregarDoArquivoCriptografado();
                    break;
                case 7:
                    System.out.println("Saindo...");
                    break;
                default:
                    System.out.println("Opção inválida!");
            }
        } while (opcao != 7);

        scanner.close();
    }

    // Método para adicionar pessoas (Aluno, Professor, Técnico Administrativo)
    public static void adicionarPessoa(Scanner scanner) {
        System.out.println("Tipo de pessoa (1- Aluno, 2- Professor, 3- Técnico Administrativo): ");
        int tipo = scanner.nextInt();
        scanner.nextLine();  // Consumir nova linha

        System.out.println("Nome: ");
        String nome = scanner.nextLine();

        System.out.println("Email: ");
        String email = scanner.nextLine();

        Pessoa pessoa = null;

        switch (tipo) {
            case 1:
                pessoa = new Aluno(nome, email);
                break;
            case 2:
                pessoa = new Professor(nome, email);
                break;
            case 3:
                pessoa = new TecnicoAdministrativo(nome, email);
                break;
            default:
                System.out.println("Tipo inválido.");
                return;
        }

        pessoas.add(pessoa);
        System.out.println("Pessoa adicionada com sucesso!");
    }

    // Listar todas as pessoas
    public static void listarPessoas() {
        if (pessoas.isEmpty()) {
            System.out.println("Nenhuma pessoa cadastrada.");
            return;
        }

        for (Pessoa pessoa : pessoas) {
            System.out.println(pessoa);
        }
    }

    // Atualizar dados de uma pessoa
    public static void atualizarPessoa(Scanner scanner) {
        System.out.println("Digite o nome da pessoa a ser atualizada: ");
        String nome = scanner.nextLine();
        Pessoa pessoa = buscarPessoaPorNome(nome);

        if (pessoa != null) {
            System.out.println("Novo nome: ");
            String novoNome = scanner.nextLine();

            System.out.println("Novo email: ");
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
        System.out.println("Digite o nome da pessoa a ser removida: ");
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

    // Salvar os dados em um arquivo de texto criptografado
    public static void salvarEmArquivoCriptografado() {
        try (FileWriter writer = new FileWriter("pessoas.txt")) {
            for (Pessoa pessoa : pessoas) {
                String pessoaCriptografada = CriptografiaUtil.criptografar(pessoa.toString());
                writer.write(pessoaCriptografada + "\n");
            }
            System.out.println("Dados criptografados e salvos com sucesso!");
        } catch (Exception e) {
            System.out.println("Erro ao salvar o arquivo.");
            e.printStackTrace();
        }
    }

    public class CriptografiaUtil {
    private static final String ALGORITMO = "AES";
    private static final String CHAVE_SECRETA = "1234567890123456"; // Exemplo de chave (16 caracteres para AES-128)

    // Método para criptografar um texto
    public static String criptografar(String texto) throws Exception {
        SecretKeySpec chaveSecreta = new SecretKeySpec(CHAVE_SECRETA.getBytes(), ALGORITMO);
        Cipher cipher = Cipher.getInstance(ALGORITMO);
        cipher.init(Cipher.ENCRYPT_MODE, chaveSecreta);
        byte[] textoCriptografado = cipher.doFinal(texto.getBytes());
        return Base64.getEncoder().encodeToString(textoCriptografado);
    }

    // Método para descriptografar um texto
    public static String descriptografar(String textoCriptografado) throws Exception {
        SecretKeySpec chaveSecreta = new SecretKeySpec(CHAVE_SECRETA.getBytes(), ALGORITMO);
        Cipher cipher = Cipher.getInstance(ALGORITMO);
        cipher.init(Cipher.DECRYPT_MODE, chaveSecreta);
        byte[] textoDescriptografado = cipher.doFinal(Base64.getDecoder().decode(textoCriptografado));
        return new String(textoDescriptografado);
    }
}

    // Carregar dados de um arquivo de texto criptografado
    public static void carregarDoArquivoCriptografado() {
        try (BufferedReader reader = new BufferedReader(new FileReader("pessoas.txt"))) {
            String linha;
            pessoas.clear();  // Limpar a lista antes de carregar novos dados
            while ((linha = reader.readLine()) != null) {
                String linhaDescriptografada = CriptografiaUtil.descriptografar(linha);
                String[] dados = linhaDescriptografada.split(", ");  // Supondo que cada campo é separado por vírgula e espaço

                if (dados.length == 2) {
                    String tipo = dados[0].split(" -> ")[0];
                    String nome = dados[0].split("Nome: ")[1];
                    String email = dados[1].split("Email: ")[1];

                    Pessoa pessoa = null;
                    if (tipo.equals("Aluno")) {
                        pessoa = new Aluno(nome, email);
                    } else if (tipo.equals("Professor")) {
                        pessoa = new Professor(nome, email);
                    } else if (tipo.equals("Técnico Administrativo")) {
                        pessoa = new TecnicoAdministrativo(nome, email);
                    }

                    if (pessoa != null) {
                        pessoas.add(pessoa);
                    }
                } else {
                    System.out.println("Formato de linha inválido: " + linhaDescriptografada);
                }
            }
            System.out.println("Dados descriptografados e carregados com sucesso!");
        } catch (Exception e) {
            System.out.println("Erro ao ler o arquivo.");
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