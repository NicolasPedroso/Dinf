//Todas as informações do jogador (Cor da peça, Dinheiro, propriedades, Ordem na vez etc)
import java.util.ArrayList;
import java.util.List;

public class Jogador {
    private String nome;
    private String cor;
    private int saldo;
    private int posicaoAtual;
    private List<CartaPropriedade> propriedades;

    public Jogador(String nome, String cor, int saldoInicial) {
        this.nome = nome;
        this.cor = cor;
        this.saldo = saldoInicial;
        this.posicaoAtual = 0;
        this.propriedades = new ArrayList<>();
    }

    // Getters
    public String getNome() { return nome; }
    public String getCor() { return cor; }
    public int getSaldo() { return saldo; }
    public int getPosicaoAtual() { return posicaoAtual; }
    public List<CartaPropriedade> getPropriedades() { return propriedades; }

    // Setters
    public void setNome(String nome) { this.nome = nome; }
    public void setCor(String cor) { this.cor = cor; }
    public void setSaldo(int saldo) { this.saldo = saldo; }
    public void setPosicaoAtual(int posicaoAtual) { this.posicaoAtual = posicaoAtual; }
}
