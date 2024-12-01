import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Propriedade {
    private int id;
    private String nome;
    private int valorCompra;
    private int[] aluguel;
    private int casas;
    private int valorCasa;
    private int valorHipoteca;

    public Propriedade(int id, String nome, int valorCompra, int[] aluguel, int casas, int valorCasa, int valorHipoteca) {
        this.id = id;
        this.nome = nome;
        this.valorCompra = valorCompra;
        this.aluguel = aluguel;
        this.casas = casas;
        this.valorCasa = valorCasa;
        this.valorHipoteca = valorHipoteca;
    }

    // Getters e Setters
    public int getId() { return id; }
    public String getNome() { return nome; }
    public int getValorCompra() { return valorCompra; }
    public int[] getAluguel() { return aluguel; }
    public int getAluguelPorCasas(int numCasas) {
        return (numCasas >= 0 && numCasas < aluguel.length) ? aluguel[numCasas] : 0;
    }
    public int getCasas() { return casas; }
    public int getValorCasa() { return valorCasa; }
    public int getValorHipoteca() { return valorHipoteca; }

    public void setId(int id) { this.id = id; }
    public void setNome(String nome) { this.nome = nome; }
    public void setValorCompra(int valorCompra) { this.valorCompra = valorCompra; }
    public void setAluguel(int[] aluguel) { this.aluguel = aluguel; }
    public void setCasas(int casas) { this.casas = casas; }
    public void setValorCasa(int valorCasa) { this.valorCasa = valorCasa; }
    public void setValorHipoteca(int valorHipoteca) { this.valorHipoteca = valorHipoteca; }

    @Override
    public String toString() {
        StringBuilder aluguelStr = new StringBuilder();
        for (int a : aluguel) {
            aluguelStr.append(a).append(" ");
        }
        return id + "; " + valorCompra + "; " + nome + "; " + aluguelStr.toString().trim() + "; " + valorCasa + "; " + valorHipoteca;
    }

    // Métodos de manipulação de propriedades

    public static List<Propriedade> carregarDeArquivo(String nomeArquivo) {
        List<Propriedade> propriedades = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(nomeArquivo))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split("; ");
                if (partes.length >= 8) {
                    try {
                        int id = Integer.parseInt(partes[0].trim());
                        int valorCompra = Integer.parseInt(partes[1].trim());
                        String nome = partes[2].trim();

                        int[] aluguel = new int[6];
                        for (int i = 0; i < 6; i++) {
                            aluguel[i] = Integer.parseInt(partes[3 + i].trim());
                        }

                        int valorCasa = Integer.parseInt(partes[9].trim());
                        int valorHipoteca = Integer.parseInt(partes[10].trim());

                        Propriedade propriedade = new Propriedade(id, nome, valorCompra, aluguel, 0, valorCasa, valorHipoteca);
                        propriedades.add(propriedade);
                    } catch (NumberFormatException e) {
                        System.out.println("Erro de formatação na linha: " + linha);
                    }
                } else if(partes.length > 5 ) {
                    try {
                        int id = Integer.parseInt(partes[0].trim());
                        int valorCompra = Integer.parseInt(partes[1].trim());
                        String nome = partes[2].trim();

                        int[] aluguel = new int[1];
                        for (int i = 0; i < 1; i++) {
                            aluguel[i] = Integer.parseInt(partes[3 + i].trim());
                        }

                        int valorCasa = Integer.parseInt(partes[4].trim());
                        int valorHipoteca = Integer.parseInt(partes[5].trim());

                        Propriedade propriedade = new Propriedade(id, nome, valorCompra, aluguel, 0, valorCasa, valorHipoteca);
                        propriedades.add(propriedade);
                    } catch (NumberFormatException e) {
                        System.out.println("Erro de formatação na linha: " + linha);
                    }
                } else {
                    System.out.println("Linha inválida ou com dados insuficientes: " + linha);
                }
            }
            System.out.println("Propriedades carregadas do arquivo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao carregar o arquivo.");
            e.printStackTrace();
        }
        return propriedades;
    }

    public static void salvarEmArquivo(List<Propriedade> propriedades, String nomeArquivo) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(nomeArquivo))) {
            for (Propriedade propriedade : propriedades) {
                writer.write(propriedade.toString() + "\n");
            }
            System.out.println("Propriedades salvas no arquivo com sucesso!");
        } catch (IOException e) {
            System.out.println("Erro ao salvar o arquivo.");
            e.printStackTrace();
        }
    }

    public static void listarPropriedades(List<Propriedade> propriedades) {
        if (propriedades.isEmpty()) {
            System.out.println("Nenhuma Propriedade cadastrada.");
        } else {
            propriedades.forEach(System.out::println);
        }
    }

    public static Propriedade buscarPropriedadePorNome(List<Propriedade> propriedades, String nome) {
        for (Propriedade propriedade : propriedades) {
            if (propriedade.getNome().equalsIgnoreCase(nome)) {
                return propriedade;
            }
        }
        return null;
    }

}
