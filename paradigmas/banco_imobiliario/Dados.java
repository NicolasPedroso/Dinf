import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class Dados /*extends JFrame implements ActionListener*/
{

    private static int dado1, dado2;
    private JDesktopPane desktop;
    private JPanel panel;
    private JButton B1;
    private JButton B2;

    public static void Rolar() {
    
        dado1 = (int)(Math.random()*6+1);
        dado2 = (int)(Math.random()*6+1);
        
        /*print soh pra teste dos numeros aleatorios*/
        System.out.println("Resultado: " + dado1 + ", " + dado2);
    }

    /*Tentativa de gerar interface (Nao sei como faz, nao fui na aula)*/
    /*public Dados()
    {

        this.desktop = new JDesktopPane();
        this.getContentPane().add( this.desktop );
        this.setSize( 500, 400 );
        this.setVisible(true);
        panel = new JPanel();
        this.getContentPane().add(panel, BorderLayout.CENTER );
        this.setSize(100,100);
        this.setVisible(true);
        this.B1 = new JButton(dado1);
        this.B2 = new JButton(dado2);
        panel.setLayout(new FlowLayout());
        panel.add(B1);
        panel.add(B2); 
    }*/
}