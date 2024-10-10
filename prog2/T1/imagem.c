#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define IMG_SIZE 256  // Supondo que a imagem seja 256x256 para simplificar

// Função para ler uma imagem no formato PGM (P2 ou P5)
int** read_pgm(const char *filename, int *rows, int *cols) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    
    char format[3];
    fscanf(fp, "%s", format);

    // Verificar se o formato é P2 (ASCII) ou P5 (binário)
    if (strcmp(format, "P2") != 0 && strcmp(format, "P5") != 0) {
        fprintf(stderr, "Formato PGM inválido!\n");
        exit(EXIT_FAILURE);
    }

    // Ler dimensões e nível máximo de cinza
    fscanf(fp, "%d %d", cols, rows);
    int max_gray;
    fscanf(fp, "%d", &max_gray);

    // Alocar memória para a imagem
    int **image = (int **)malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++)
        image[i] = (int *)malloc(*cols * sizeof(int));

    // Ler pixels (ASCII ou binário)
    if (strcmp(format, "P2") == 0) {
        for (int i = 0; i < *rows; i++)
            for (int j = 0; j < *cols; j++)
                fscanf(fp, "%d", &image[i][j]);
    } else if (strcmp(format, "P5") == 0) {
        fgetc(fp);  // Ignorar o byte de nova linha
        for (int i = 0; i < *rows; i++)
            fread(image[i], sizeof(int), *cols, fp);
    }

    fclose(fp);
    return image;
}

// Função para salvar uma imagem PGM (P2 - ASCII)
void write_pgm(const char *filename, int **image, int rows, int cols) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Erro ao abrir o arquivo para escrita");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "P2\n%d %d\n255\n", cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fp, "%d ", image[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// Função para calcular o LBP de um pixel
int calculate_lbp(int **image, int x, int y, int rows, int cols) {
    int lbp_val = 0;
    int center = image[x][y];
    int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, 
        {1, 1}, {1, 0}, {1, -1}, {0, -1}
    };
    for (int i = 0; i < 8; i++) {
        int new_x = x + offsets[i][0];
        int new_y = y + offsets[i][1];
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols) {
            if (image[new_x][new_y] >= center) {
                lbp_val |= (1 << i);
            }
        }
    }
    return lbp_val;
}

// Função para gerar a imagem LBP
int** generate_lbp_image(int **image, int rows, int cols) {
    int **lbp_image = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        lbp_image[i] = (int *)malloc(cols * sizeof(int));

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            lbp_image[i][j] = calculate_lbp(image, i, j, rows, cols);
        }
    }

    return lbp_image;
}

// Função para gerar o histograma da imagem LBP
void generate_histogram(int **lbp_image, int rows, int cols, int *histogram) {
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            histogram[lbp_image[i][j]]++;
        }
    }
}

// Função para calcular a distância Euclidiana entre dois histogramas
double calculate_euclidean_distance(int *hist1, int *hist2, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += pow(hist1[i] - hist2[i], 2);
    }
    return sqrt(sum);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Uso: ./lbp -d <dir_base> -i <img_test>\n");
        exit(EXIT_FAILURE);
    }

    // Ler a imagem de teste
    int rows, cols;
    int **image = read_pgm(argv[4], &rows, &cols);

    // Gerar a imagem LBP
    int **lbp_image = generate_lbp_image(image, rows, cols);

    // Gerar o histograma da imagem de teste
    int hist_test[256];
    generate_histogram(lbp_image, rows, cols, hist_test);

    // TODO: Carregar as imagens da base de referência e comparar os histogramas

    // Exemplo: Gerar a saída da imagem LBP
    write_pgm("img_lbp_output.pgm", lbp_image, rows, cols);

    // Liberar memória
    for (int i = 0; i < rows; i++) {
        free(image[i]);
        free(lbp_image[i]);
    }
    free(image);
    free(lbp_image);

    return 0;
}
