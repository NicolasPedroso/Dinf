import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Carta {
    private int id;
    private String tipo;
    private String descricao;
    private int valorEfeito;

    public Carta(int id, String tipo, String descricao, int valorEfeito) {
        this.id = id;
        this.tipo = tipo;
        this.descricao = descricao;
        this.valorEfeito = valorEfeito;
    }

    // Getters
    public int getId() { return id; }
    public String getTipo() { return tipo; }
    public String getDescricao() { return descricao; }
    public int getValorEfeito() { return valorEfeito; }

    // Setters
    public void setId(int id) { this.id = id; }
    public void setTipo(String tipo) { this.tipo = tipo; }
    public void setDescricao(String descricao) { this.descricao = descricao; }
    public void setValorEfeito(int valorEfeito) { this.valorEfeito = valorEfeito; }

    @Override
    public String toString() {
        return id + "; " + tipo + "; " + descricao + "; " + valorEfeito;
    }

    public static List<Carta> carregarDeArquivo(String nomeArquivo) {
        List<Carta> cartas = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split("; ");
                if (partes.length >= 4) {
                    try {
                        int id = Integer.parseInt(partes[0].trim());
                        String tipo = partes[1].trim();
                        String descricao = partes[2].trim();
                        int valorEfeito = Integer.parseInt(partes[3].trim());

                        Carta carta = new Carta(id, tipo, descricao, valorEfeito);
                        cartas.add(carta);
                    } catch (NumberFormatException e) {
                        System.out.println("Erro de formatação na linha: " + linha);
                    }
                } else if (partes.length >= 3) {
                    try {
                        int id = Integer.parseInt(partes[0].trim());
                        String tipo = partes[1].trim();
                        String descricao = partes[2].trim();
                        int valorEfeito = 0;

                        Carta carta = new Carta(id, tipo, descricao, valorEfeito);
                        cartas.add(carta);
                    } catch (NumberFormatException e) {
                        System.out.println("Erro de formatação na linha: " + linha);
                    }
                } else {
                    System.out.println("Linha inválida ou com dados insuficientes: " + linha);
                }
            }
            System.out.println("Cartas carregadas do arquivo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao carregar o arquivo.");
            e.printStackTrace();
        }
        return cartas;
    }

    public static void salvarEmArquivo(List<Carta> cartas, String nomeArquivo) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(nomeArquivo))) {
            for (Carta carta : cartas) {
                writer.write(carta.toString() + "\n");
            }
            System.out.println("Cartas salvas no arquivo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao salvar o arquivo.");
            e.printStackTrace();
        }
    }

    public static void listarCartas(List<Carta> cartas) {
        if (cartas.isEmpty()) {
            System.out.println("Nenhuma carta cadastrada.");
        } else {
            cartas.forEach(System.out::println);
        }
    }

    public static void adicionarSorteAzar(List<Carta> cartas, Scanner scanner) {
        System.out.print("ID: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // Consumir nova linha

        System.out.print("Tipo: ");
        String tipo = scanner.nextLine();

        System.out.print("Descrição: ");
        String descricao = scanner.nextLine();

        System.out.print("Valor do efeito: ");
        int valorEfeito = scanner.nextInt();

        Carta carta = new Carta(id, tipo, descricao, valorEfeito);
        cartas.add(carta);
        System.out.println("Carta adicionada com sucesso!");
    }

    public static void atualizarSorteAzar(List<Carta> cartas, Scanner scanner) {
        System.out.print("Digite o ID da carta a ser atualizada: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // Consumir nova linha

        Carta carta = buscarCarta(cartas, id);
        if (carta != null) {
            System.out.print("Novo tipo: ");
            String tipo = scanner.nextLine();

            System.out.print("Nova descrição: ");
            String descricao = scanner.nextLine();

            System.out.print("Novo valor do efeito: ");
            int valorEfeito = scanner.nextInt();

            carta.setTipo(tipo);
            carta.setDescricao(descricao);
            carta.setValorEfeito(valorEfeito);

            System.out.println("Carta atualizada com sucesso!");
        } else {
            System.out.println("Carta não encontrada.");
        }
    }

    public static void removerSorteAzar(List<Carta> cartas, Scanner scanner) {
        System.out.print("Digite o ID da carta a ser removida: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // Consumir nova linha

        Carta carta = buscarCarta(cartas, id);
        if (carta != null) {
            cartas.remove(carta);
            System.out.println("Carta removida com sucesso!");
        } else {
            System.out.println("Carta não encontrada.");
        }
    }

    public static Carta buscarCarta(List<Carta> cartas, int id) {
        for (Carta carta : cartas) {
            if (carta.getId() == id) {
                return carta;
            }
        }
        return null;
    }
}
