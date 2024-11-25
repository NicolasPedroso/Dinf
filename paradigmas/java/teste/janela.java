import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class JanelaSimples extends JFrame {

    public JanelaSimples() {
        // Configurações da janela
        setTitle("Janela Simples");
        setSize(1920, 1080);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(null);  // Layout absoluto para posicionar componentes manualmente

        // Cria um botão
        JButton botao = new JButton("Clique aqui");
        botao.setBounds((1920/2-200), (1080/2-200), 400, 400);  // Posiciona o botão na janela (x, y, largura, altura)

        // Adiciona um ActionListener ao botão
        botao.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Mostra uma caixa de diálogo quando o botão é clicado
                JOptionPane.showMessageDialog(JanelaSimples.this, "Você clicou no botão!", "Mensagem", JOptionPane.INFORMATION_MESSAGE);
            }
        });

        // Adiciona o botão à janela
        add(botao);

        // Torna a janela visível
        setVisible(true);
    }

    public static void main(String[] args) {
        new JanelaSimples();  // Inicializa a janela
    }
}
