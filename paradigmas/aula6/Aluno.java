class Aluno {
    private String nome;
    private String endereco;
    private String email;
    private String telefone;
    private int[] nota;

    // Construtor para inicializar o array de notas
    public Aluno() {
        this.nota = new int[4];
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return this.nome;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public String getEndereco() {
        return this.endereco;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getEmail() {
        return this.email;
    }

    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }

    public String getTelefone() {
        return this.telefone;
    }

    public void setNota(int index, int nota) {
        this.nota[index] = nota;
    }

    public int getNota(int index) {
        return this.nota[index];
    }

    // Sobrescreve o método toString para imprimir as informações do aluno
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Nome: ").append(this.nome).append("\n");
        sb.append("Endereço: ").append(this.endereco).append("\n");
        sb.append("Email: ").append(this.email).append("\n");
        sb.append("Telefone: ").append(this.telefone).append("\n");
        sb.append("Notas: ");
        for (int i = 0; i < nota.length; i++) {
            sb.append(nota[i]);
            if (i < nota.length - 1) {
                sb.append(", ");
            }
        }
        sb.append("\n");
        return sb.toString();
    }
}
