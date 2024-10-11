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
void compareWithBase(const char *basePath, const char *testImagePath) {
    DIR* dir;
    struct dirent* entry;
    struct stat fileStat;
    float minDistance = FLT_MAX;
    char mostSimilarImage[1024]; // Para armazenar o nome da imagem mais similar

    // Carregar a imagem de teste
    PGMImage* testImage = readPGM(testImagePath);
    if (testImage == NULL) {
        fprintf(stderr, "Erro ao ler a imagem de teste\n");
        return;
    }

    // Comparar com cada imagem no diretório base
    if ((dir = opendir(basePath)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            // Construir o caminho do arquivo
            char filePath[1024];
            snprintf(filePath, sizeof(filePath), "%s/%s", basePath, entry->d_name);

            // Verifica se é um arquivo regular
            if (stat(filePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
                PGMImage* baseImage = readPGM(filePath);
                if (baseImage == NULL) {
                    continue; // Ignora erros na leitura da imagem da base
                }

                float distance = compareImages(testImage, baseImage);
                if (distance < minDistance) {
                    minDistance = distance;
                    strcpy(mostSimilarImage, entry->d_name); // Armazena o nome da imagem mais similar
                }

                freePGM(baseImage); // Libera a imagem da base
            }
        }
        closedir(dir);
    } else {
        perror("Não foi possível abrir o diretório");
    }

    if (minDistance < FLT_MAX) {
        printf("Imagem mais similar: %s %.6f\n", mostSimilarImage, minDistance);
    } else {
        printf("Nenhuma imagem similar encontrada.\n");
    }

    freePGM(testImage); // Libera a imagem de teste
}


// Função para comparar duas imagens usando LBP
float compareImages(PGMImage *img1, PGMImage *img2) {
    if (img1->width != img2->width || img1->height != img2->height) {
        fprintf(stderr, "As imagens devem ter as mesmas dimensões para comparação.\n");
        return FLT_MAX; // Distância máxima se as dimensões não correspondem
    }

    // Aloca as imagens LBP
    unsigned char **lbp_image1 = allocateLBPImage(img1->width - 2, img1->height - 2);
    unsigned char **lbp_image2 = allocateLBPImage(img2->width - 2, img2->height - 2);

    // Calcula o LBP para ambas as imagens
    calculateLBP(img1, lbp_image1);
    calculateLBP(img2, lbp_image2);

    // Calcula os histogramas das imagens LBP
    float histogram1[HISTOGRAM_SIZE];
    float histogram2[HISTOGRAM_SIZE];
    calculateLBPHistogram(lbp_image1, img1->width - 2, img1->height - 2, histogram1);
    calculateLBPHistogram(lbp_image2, img2->width - 2, img2->height - 2, histogram2);

    // Calcula a distância entre os histogramas
    float distance = euclideanDistance(histogram1, histogram2, HISTOGRAM_SIZE);

    // Libera a memória das imagens LBP
    for (int i = 0; i < img1->height - 2; i++) {
        free(lbp_image1[i]);
        free(lbp_image2[i]);
    }
    free(lbp_image1);
    free(lbp_image2);

    return distance;
}

// Função para gerar a imagem LBP a partir de uma imagem de entrada
void generateLBPImage(const char *input_image_path, const char *output_image_path) {
    PGMImage *img = readPGM(input_image_path);
    if (!img) {
        fprintf(stderr, "Erro ao ler a imagem %s\n", input_image_path);
        return;
    }

    unsigned char **lbp_image = allocateLBPImage(img->width - 2, img->height - 2);
    if (!lbp_image) {
        freePGM(img);
        return;
    }

    calculateLBP(img, lbp_image);

    // Salvar a imagem LBP (implementação omitida)

    freePGM(img);
    for (int i = 0; i < img->height - 2; i++) {
        free(lbp_image[i]);
    }
    free(lbp_image);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s -d <diretório_base> -i <imagem_teste>\n", argv[0]);
        return 1;
    }

    const char *base_dir = NULL;
    const char *test_image = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            base_dir = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            test_image = argv[++i];
        }
    }

    if (!base_dir || !test_image) {
        fprintf(stderr, "Diretório base e imagem de teste são obrigatórios.\n");
        return 1;
    }

    compareWithBase(base_dir, test_image);
    return 0;
}
