#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <strings.h> // Para strcasecmp

#define HISTOGRAM_SIZE 256

// Estrutura para armazenar a imagem PGM
typedef struct {
    char format[3]; // "P5"
    int width, height, max_val;
    unsigned char **pixels;
} PGMImage;

// Funções declaradas
PGMImage* readPGM(const char *filename);
void freePGM(PGMImage *img);
unsigned char** allocateLBPImage(int width, int height);
void calculateLBP(PGMImage *img, unsigned char **lbp_image);
void calculateLBPHistogram(unsigned char **lbp_image, int width, int height, float *histogram);
float euclideanDistance(float *hist1, float *hist2, int size);
void compareWithBase(const char *base_dir, const char *test_image_path);
void generateLBPImage(const char *input_image_path, const char *output_image_path);

// Função para ler arquivo PGM (apenas P5 para este caso)
PGMImage* readPGM(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    PGMImage *img = (PGMImage*)malloc(sizeof(PGMImage));
    if (!img) {
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        fclose(file);
        return NULL;
    }

    // Lê o formato da imagem
    if (fscanf(file, "%2s", img->format) != 1 || strcmp(img->format, "P5") != 0) {
        fprintf(stderr, "Formato de imagem inválido (%s) em %s! Apenas P5 é suportado.\n", img->format, filename);
        free(img);
        fclose(file);
        return NULL;
    }

    // Lê as dimensões da imagem
    if (fscanf(file, "%d %d", &img->width, &img->height) != 2 || img->width <= 2 || img->height <= 2) {
        fprintf(stderr, "Erro ao ler a largura e altura da imagem em %s\n", filename);
        free(img);
        fclose(file);
        return NULL;
    }

    // Lê o valor máximo de cinza
    if (fscanf(file, "%d", &img->max_val) != 1) {
        fprintf(stderr, "Erro ao ler o valor máximo de cinza em %s\n", filename);
        free(img);
        fclose(file);
        return NULL;
    }

    fgetc(file); // Pula o caractere de nova linha após o cabeçalho

    // Aloca memória para os pixels
    img->pixels = (unsigned char **)malloc(img->height * sizeof(unsigned char *));
    if (!img->pixels) {
        fprintf(stderr, "Erro ao alocar memória para os pixels.\n");
        free(img);
        fclose(file);
        return NULL;
    }

    // Lê os dados da imagem P5 (binário)
    for (int i = 0; i < img->height; i++) {
        img->pixels[i] = (unsigned char *)malloc(img->width * sizeof(unsigned char));
        if (!img->pixels[i]) {
            fprintf(stderr, "Erro ao alocar memória para a linha %d dos pixels.\n", i);
            for (int k = 0; k < i; k++) free(img->pixels[k]);
            free(img->pixels);
            free(img);
            fclose(file);
            return NULL;
        }

        if (fread(img->pixels[i], sizeof(unsigned char), img->width, file) != img->width) {
            fprintf(stderr, "Erro ao ler os pixels binários na linha %d em %s\n", i, filename);
            for (int k = 0; k <= i; k++) free(img->pixels[k]);
            free(img->pixels);
            free(img);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return img;
}

// Função para liberar a memória da imagem
void freePGM(PGMImage *img) {
    if (img) {
        if (img->pixels) {
            for (int i = 0; i < img->height; i++) {
                free(img->pixels[i]);
            }
            free(img->pixels);
        }
        free(img);
    }
}

// Função para alocar imagem LBP
unsigned char** allocateLBPImage(int width, int height) {
    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Largura ou altura inválida para a imagem LBP: %d x %d\n", width, height);
        return NULL;
    }

    unsigned char **lbp_image = (unsigned char **)malloc(height * sizeof(unsigned char *));
    if (!lbp_image) {
        fprintf(stderr, "Erro ao alocar memória para a imagem LBP.\n");
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        lbp_image[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
        if (!lbp_image[i]) {
            fprintf(stderr, "Erro ao alocar memória para a linha %d da imagem LBP.\n", i);
            for (int k = 0; k < i; k++) free(lbp_image[k]);
            free(lbp_image);
            return NULL;
        }
    }
    return lbp_image;
}

// Função para calcular o LBP de uma imagem
void calculateLBP(PGMImage *img, unsigned char **lbp_image) {
    for (int i = 1; i < img->height - 1; i++) {
        for (int j = 1; j < img->width - 1; j++) {
            unsigned char central_pixel = img->pixels[i][j];
            unsigned char lbp_value = 0;

            lbp_value |= (img->pixels[i-1][j-1] >= central_pixel) << 7;
            lbp_value |= (img->pixels[i-1][j] >= central_pixel) << 6;
            lbp_value |= (img->pixels[i-1][j+1] >= central_pixel) << 5;
            lbp_value |= (img->pixels[i][j+1] >= central_pixel) << 4;
            lbp_value |= (img->pixels[i+1][j+1] >= central_pixel) << 3;
            lbp_value |= (img->pixels[i+1][j] >= central_pixel) << 2;
            lbp_value |= (img->pixels[i+1][j-1] >= central_pixel) << 1;
            lbp_value |= (img->pixels[i][j-1] >= central_pixel) << 0;

            lbp_image[i-1][j-1] = lbp_value;
        }
    }
}

// Função para calcular o histograma de uma imagem LBP
void calculateLBPHistogram(unsigned char **lbp_image, int width, int height, float *histogram) {
    // Inicializa o histograma com zeros
    for (int i = 0; i < HISTOGRAM_SIZE; i++) {
        histogram[i] = 0.0f;
    }

    // Preenche o histograma
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            histogram[lbp_image[i][j]] += 1.0f;
        }
    }

    // Normaliza o histograma
    int total_pixels = width * height;
    for (int i = 0; i < HISTOGRAM_SIZE; i++) {
        histogram[i] /= (float)total_pixels;
    }
}

// Função para calcular a distância Euclidiana entre dois histogramas
float euclideanDistance(float *hist1, float *hist2, int size) {
    float distance = 0.0f;
    for (int i = 0; i < size; i++) {
        float diff = hist1[i] - hist2[i];
        distance += diff * diff;
    }
    return sqrt(distance);
}

// Função para comparar uma imagem de teste com todas as imagens da base
void compareWithBase(const char *base_dir, const char *test_image_path) {
    DIR *dir;
    struct dirent *entry;

    // Abre o diretório da base de imagens
    if ((dir = opendir(base_dir)) == NULL) {
        perror("Erro ao abrir o diretório da base de imagens");
        return;
    }

    // Lê a imagem de teste
    PGMImage *test_image = readPGM(test_image_path);
    if (test_image == NULL) {
        closedir(dir);
        return;
    }

    // Aloca imagem LBP para a imagem de teste
    unsigned char **test_lbp = allocateLBPImage(test_image->width - 2, test_image->height - 2);
    if (test_lbp == NULL) {
        freePGM(test_image);
        closedir(dir);
        return;
    }

    // Calcula o LBP da imagem de teste
    calculateLBP(test_image, test_lbp);

    // Calcula o histograma da imagem de teste
    float test_histogram[HISTOGRAM_SIZE];
    calculateLBPHistogram(test_lbp, test_image->width - 2, test_image->height - 2, test_histogram);

    float min_distance = INFINITY; // Inicializa com infinito
    char similar_image[256] = {0};

    // Percorre cada arquivo no diretório da base
    while ((entry = readdir(dir)) != NULL) {
        char *dot = strrchr(entry->d_name, '.');
        if (dot && (strcasecmp(dot, ".pgm") == 0)) {
            char image_path[512];
            snprintf(image_path, sizeof(image_path), "%s/%s", base_dir, entry->d_name);

            PGMImage *base_image = readPGM(image_path);
            if (base_image == NULL) {
                continue;
            }

            unsigned char **base_lbp = allocateLBPImage(base_image->width - 2, base_image->height - 2);
            if (base_lbp == NULL) {
                freePGM(base_image);
                continue;
            }

            calculateLBP(base_image, base_lbp);
            float base_histogram[HISTOGRAM_SIZE];
            calculateLBPHistogram(base_lbp, base_image->width - 2, base_image->height - 2, base_histogram);

            float distance = euclideanDistance(test_histogram, base_histogram, HISTOGRAM_SIZE);

            if (distance < min_distance) {
                min_distance = distance;
                strncpy(similar_image, entry->d_name, sizeof(similar_image) - 1);
                similar_image[sizeof(similar_image) - 1] = '\0'; // Garantir que a string está terminada
            }

            freePGM(base_image);
            for (int i = 0; i < base_image->height - 2; i++) {
                free(base_lbp[i]);
            }
            free(base_lbp);
        }
    }

    closedir(dir);

    if (strlen(similar_image) > 0) {
        printf("Imagem mais similar: %s com distância %.6f\n", similar_image, min_distance);
    } else {
        printf("Nenhuma imagem válida encontrada na base.\n");
    }

    freePGM(test_image);
    for (int i = 0; i < test_image->height - 2; i++) {
        free(test_lbp[i]);
    }
    free(test_lbp);
}

// Função para gerar a imagem LBP e salvá-la como arquivo PGM
void generateLBPImage(const char *input_image_path, const char *output_image_path) {
    PGMImage *input_image = readPGM(input_image_path);
    if (input_image == NULL) {
        return;
    }

    unsigned char **lbp_image = allocateLBPImage(input_image->width - 2, input_image->height - 2);
    if (lbp_image == NULL) {
        freePGM(input_image);
        return;
    }

    // Calcula o LBP da imagem
    calculateLBP(input_image, lbp_image);

    // Salva a imagem LBP no formato PGM
    FILE *file = fopen(output_image_path, "wb");
    if (!file) {
        fprintf(stderr, "Erro ao salvar a imagem LBP em %s\n", output_image_path);
        freePGM(input_image);
        for (int i = 0; i < input_image->height - 2; i++) {
            free(lbp_image[i]);
        }
        free(lbp_image);
        return;
    }

    // Escreve o cabeçalho da imagem P5
    fprintf(file, "P5\n%d %d\n%d\n", input_image->width - 2, input_image->height - 2, input_image->max_val);
    
    // Escreve os dados da imagem LBP
    for (int i = 0; i < input_image->height - 2; i++) {
        fwrite(lbp_image[i], sizeof(unsigned char), input_image->width - 2, file);
    }

    fclose(file);

    // Libera a memória
    freePGM(input_image);
    for (int i = 0; i < input_image->height - 2; i++) {
        free(lbp_image[i]);
    }
    free(lbp_image);
}

// Função principal para gerenciar argumentos e chamar as funções corretas
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: ./LBP -d <diretorio> -i <imagem>\nOu: ./LBP -i <imagem> -o <imagem_saida>\n");
        return 1;
    }

    if (strcmp(argv[1], "-d") == 0 && strcmp(argv[3], "-i") == 0 && argc == 5) {
        // Compara uma imagem de teste com a base de referência
        const char *base_dir = argv[2];
        const char *test_image_path = argv[4];
        compareWithBase(base_dir, test_image_path);
    } else if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0 && argc == 5) {
        // Gera uma imagem LBP
        const char *input_image_path = argv[2];
        const char *output_image_path = argv[4];
        generateLBPImage(input_image_path, output_image_path);
    } else {
        printf("Comando inválido! Uso: ./LBP -d <diretorio> -i <imagem>\nOu: ./LBP -i <imagem> -o <imagem_saida>\n");
        return 1;
    }

    return 0;
}