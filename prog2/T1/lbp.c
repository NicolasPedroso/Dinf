#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Para manipulação de diretórios
#include <float.h>  // Para FLT_MAX
#include <math.h>   // Para funções matemáticas
#include <stdbool.h> // Para o tipo bool
#include <sys/stat.h> // Para a função stat

#define HISTOGRAM_SIZE 256

// Estrutura para armazenar a imagem PGM
typedef struct {
    char format[3]; // "P5"
    int width, height, max_val;
    unsigned char **pixels;
} PGMImage;

// Declaração de funções
PGMImage* readPGM(const char *filename);
void freePGM(PGMImage *img);
unsigned char** allocateLBPImage(int width, int height);
void calculateLBP(PGMImage *img, unsigned char **lbp_image);
void calculateLBPHistogram(unsigned char **lbp_image, int width, int height, float *histogram);
float euclideanDistance(float *hist1, float *hist2, int size);
void compareWithBase(const char *base_dir, const char *test_image_path);
void generateLBPImage(const char *input_image_path, const char *output_image_path);
float compareImages(PGMImage *img1, PGMImage *img2);

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
    DIR* dir;
    struct dirent* entry;
    struct stat fileStat;

    PGMImage* testImage = readPGM(test_image_path);
    if (testImage == NULL) {
        fprintf(stderr, "Erro ao ler a imagem de teste\n");
        return;
    }

    float minDistance = FLT_MAX;
    char *mostSimilarImage = NULL;

    dir = opendir(base_dir);
    if (dir == NULL) {
        perror("Não foi possível abrir o diretório");
        freePGM(testImage);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", base_dir, entry->d_name);

        if (stat(filePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            PGMImage* baseImage = readPGM(filePath);
            if (baseImage == NULL) {
                continue;
            }

            float distance = compareImages(testImage, baseImage);
            if (distance < minDistance) {
                minDistance = distance;
                if (mostSimilarImage) {
                    free(mostSimilarImage);
                }
                // Substituir strdup por malloc e strcpy para maior portabilidade
                mostSimilarImage = (char *)malloc(strlen(entry->d_name) + 1);
                if (mostSimilarImage) {
                    strcpy(mostSimilarImage, entry->d_name);
                } else {
                    fprintf(stderr, "Erro ao alocar memória para o nome da imagem mais similar.\n");
                }
            }

            freePGM(baseImage);
        }
    }
    closedir(dir);

    if (mostSimilarImage) {
        printf("Imagem mais similar: %s %.6f\n", mostSimilarImage, minDistance);
        free(mostSimilarImage);
    } else {
        printf("Nenhuma imagem similar encontrada.\n");
    }

    freePGM(testImage);
}

// Função para comparar duas imagens usando LBP
float compareImages(PGMImage *img1, PGMImage *img2) {
    float hist1[HISTOGRAM_SIZE];
    float hist2[HISTOGRAM_SIZE];
    unsigned char **lbp1 = allocateLBPImage(img1->width - 2, img1->height - 2);
    unsigned char **lbp2 = allocateLBPImage(img2->width - 2, img2->height - 2);

    if (!lbp1 || !lbp2) {
        fprintf(stderr, "Erro ao alocar memória para imagens LBP durante a comparação.\n");
        if (lbp1) {
            for (int i = 0; i < img1->height - 2; i++) free(lbp1[i]);
            free(lbp1);
        }
        if (lbp2) {
            for (int i = 0; i < img2->height - 2; i++) free(lbp2[i]);
            free(lbp2);
        }
        return FLT_MAX; // Retorna a maior distância possível em caso de erro
    }

    calculateLBP(img1, lbp1);
    calculateLBP(img2, lbp2);

    calculateLBPHistogram(lbp1, img1->width - 2, img1->height - 2, hist1);
    calculateLBPHistogram(lbp2, img2->width - 2, img2->height - 2, hist2);

    float distance = euclideanDistance(hist1, hist2, HISTOGRAM_SIZE);

    for (int i = 0; i < img1->height - 2; i++) {
        free(lbp1[i]);
    }
    free(lbp1);

    for (int i = 0; i < img2->height - 2; i++) {
        free(lbp2[i]);
    }
    free(lbp2);
    
    return distance;
}

// Função para gerar a imagem LBP e salvar em um arquivo
void generateLBPImage(const char *input_image_path, const char *output_image_path) {
    PGMImage *img = readPGM(input_image_path);
    if (!img) {
        return; // Falha ao abrir a imagem
    }

    // Armazena width e height antes de liberar img
    int width = img->width;
    int height = img->height;

    unsigned char **lbp_image = allocateLBPImage(width - 2, height - 2);
    if (!lbp_image) {
        freePGM(img);
        return;
    }

    calculateLBP(img, lbp_image);

    // Salvar a imagem LBP
    FILE *output_file = fopen(output_image_path, "wb");
    if (!output_file) {
        fprintf(stderr, "Erro ao criar o arquivo de saída %s\n", output_image_path);
        // Libera a memória em caso de falha
        for (int i = 0; i < height - 2; i++) { // Usa height armazenado
            free(lbp_image[i]);
        }
        free(lbp_image);
        freePGM(img);
        return;
    }

    // Escreve o cabeçalho da imagem PGM
    fprintf(output_file, "P5\n%d %d\n255\n", width - 2, height - 2);

    // Escreve os dados da imagem LBP
    for (int i = 0; i < height - 2; i++) { // Usa height armazenado
        fwrite(lbp_image[i], sizeof(unsigned char), width - 2, output_file);
    }

    fclose(output_file);
    freePGM(img);
    for (int i = 0; i < height - 2; i++) { // Usa height armazenado
        free(lbp_image[i]);
    }
    free(lbp_image);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s [-d <diretorio_base>] -i <imagem_entrada> [-o <imagem_saida>]\n", argv[0]);
        return 1;
    }

    const char *input_image_path = NULL;
    const char *output_image_path = NULL;
    const char *base_dir = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_image_path = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_image_path = argv[++i];
        } else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            base_dir = argv[++i];
        }
    }

    if (input_image_path && base_dir) {
        // Compara com a base de imagens
        compareWithBase(base_dir, input_image_path);
    }

    if (input_image_path && output_image_path) {
        // Gera a imagem LBP
        generateLBPImage(input_image_path, output_image_path);
    }

    if ((!input_image_path || !base_dir) && (!input_image_path || !output_image_path)) {
        fprintf(stderr, "Argumentos insuficientes ou inválidos.\n");
        fprintf(stderr, "Uso: %s [-d <diretorio_base>] -i <imagem_entrada> [-o <imagem_saida>]\n", argv[0]);
        return 1;
    }

    return 0;
}
