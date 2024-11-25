import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Exemplo0303 {
    public static void main(String args[]) {
        int num1, num2;
        try {
            BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Digite o numero:");
            num1 = Integer.parseInt(teclado.readLine());
            System.out.println("Digite o numero:");
            num2 = Integer.parseInt(teclado.readLine());
            
            System.out.println("Soma = " + (num1 + num2));
            System.out.println("Subtracao = " + (num1 - num2));
            System.out.println("Multiplicacao = " + (num1 * num2));
            System.out.println("Divisao = " + (num1 / num2));
        } catch (ArithmeticException aex) {
            System.out.println("Erro de divisao por zero! " + aex);
        } catch (IOException ioex) {
            System.out.println("Erro de leitura de entrada! " + ioex);
        } catch (NumberFormatException nfex) {
            System.out.println("Digite apenas numeros inteiros! " + nfex);
        } finally {
            System.out.println("Fim!");
        }
    }
}
