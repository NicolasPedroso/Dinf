#include "lbp.h"
#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <float.h>
#include <math.h>
#include <sys/stat.h>

/*Funcao para alocar a imagem LBP*/
unsigned char** criaImageLBP(int largura, int altura) {
    if (largura <= 0 || altura <= 0) {
        /*Debugging print*/
        fprintf(stderr, "Largura ou altura inválida para a imagem LBP: %d x %d\n", largura, altura);
        /**/
        return NULL;
    }

    unsigned char **imagemLBP = (unsigned char **)malloc(altura * sizeof(unsigned char *));
    if (!imagemLBP) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao alocar memória para a imagem LBP.\n");
        /**/
        return NULL;
    }

    for (int i = 0; i < altura; i++) {
        imagemLBP[i] = (unsigned char *)malloc(largura * sizeof(unsigned char));
        if (!imagemLBP[i]) {
            /*Debugging print*/
            fprintf(stderr, "Erro ao alocar memória para a linha %d da imagem LBP.\n", i);
            /**/
            for (int k = 0; k < i; k++) free(imagemLBP[k]);
            free(imagemLBP);
            return NULL;
        }
    }
    return imagemLBP;
}

/*Funcao para liberar a imagem LBP*/
void liberaImagemLBP(unsigned char **imagemLBP, int altura) {
    if (imagemLBP) {
        for (int i = 0; i < altura; i++) {
            free(imagemLBP[i]);
        }
        free(imagemLBP);
    }
}

/*Funcao para calcular o LBP de uma imagem*/
void calculaLBP(imagemPGM *img, unsigned char **imagemLBP) {
    for (int i = 1; i < img->altura - 1; i++) {
        for (int j = 1; j < img->largura - 1; j++) {
            unsigned char pixelCentral = img->pixels[i][j];
            unsigned char valorLBP = 0;

            valorLBP |= (img->pixels[i-1][j-1] >= pixelCentral) << 7;
            valorLBP |= (img->pixels[i-1][j] >= pixelCentral) << 6;
            valorLBP |= (img->pixels[i-1][j+1] >= pixelCentral) << 5;
            valorLBP |= (img->pixels[i][j+1] >= pixelCentral) << 4;
            valorLBP |= (img->pixels[i+1][j+1] >= pixelCentral) << 3;
            valorLBP |= (img->pixels[i+1][j] >= pixelCentral) << 2;
            valorLBP |= (img->pixels[i+1][j-1] >= pixelCentral) << 1;
            valorLBP |= (img->pixels[i][j-1] >= pixelCentral) << 0;

            imagemLBP[i-1][j-1] = valorLBP;
        }
    }
}

/*Funcao para calcular o histograma LBP de uma imagem*/
void calculahistogramaLBP(unsigned char **imagemLBP, int largura, int altura, float *histograma) {
    /*Inicializa o histograma com zeros*/
    for (int i = 0; i < HISTOGRAM_SIZE; i++) {
        histograma[i] = 0.0f;
    }

    /*Preenche o histograma*/
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            histograma[imagemLBP[i][j]] += 1.0f;
        }
    }

    /*Normaliza o histograma*/
    int pixelsTotal = largura * altura;
    for (int i = 0; i < HISTOGRAM_SIZE; i++) {
        histograma[i] /= (float)pixelsTotal;
    }
}

/*Funcao para calcular a distancia Euclidiana entre dois histogramas*/
float distanciaEuclidiana(float *hist1, float *hist2, int tam) {
    float distancia = 0.0f;
    for (int i = 0; i < tam; i++) {
        float diferenca = hist1[i] - hist2[i];
        distancia += diferenca * diferenca;
    }
    return sqrt(distancia);
}

/*Funcao para comparar uma imagem de teste com todas as imagens da base*/
void comparaBase(const char *baseDir, const char *imagemTeste) {
    DIR* dir;
    struct dirent* entrada;
    struct stat fileStat;

    imagemPGM* testeImagem = lerPGM(imagemTeste);
    if (testeImagem == NULL) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao ler a imagem de teste.\n");
        /**/
        return;
    }

    float distanciaMinima = FLT_MAX;
    char *maisSimilar = NULL;

    dir = opendir(baseDir);
    if (dir == NULL) {
        /*Debugging print*/
        perror("Não foi possível abrir o diretório da base de imagens");
        /**/
        liberaPGM(testeImagem);
        return;
    }

    while ((entrada = readdir(dir)) != NULL) {
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", baseDir, entrada->d_name);

        if (stat(filePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            imagemPGM* imagemBase = lerPGM(filePath);
            if (imagemBase == NULL) {
                continue;
            }

            float distancia = comparaImagens(testeImagem, imagemBase);
            if (distancia < distanciaMinima) {
                distanciaMinima = distancia;
                if (maisSimilar) {
                    free(maisSimilar);
                }
                maisSimilar = (char *)malloc(strlen(entrada->d_name) + 1);
                if (maisSimilar) {
                    strcpy(maisSimilar, entrada->d_name);
                } else {
                    /*Debugging print*/
                    fprintf(stderr, "Erro ao alocar memória para o nome da imagem mais similar.\n");
                    /**/
                }
            }

            liberaPGM(imagemBase);
        }
    }
    closedir(dir);

    if (maisSimilar) {
        printf("Imagem mais similar: %s %.2f\n", maisSimilar, distanciaMinima);
        free(maisSimilar);
    } else {
        printf("Nenhuma imagem similar encontrada.\n");
    }

    liberaPGM(testeImagem);
}

/*Funcao para gerar uma imagem LBP a partir de uma imagem de entrada*/
void geraimagemLBP(const char *imagemEntrada, const char *imagemSaida) {
    imagemPGM *img = lerPGM(imagemEntrada);
    if (!img) {
        return; /*Falha ao abrir a imagem*/
    }

    /*Armazena largura e altura antes de liberar img*/
    int largura = img->largura;
    int altura = img->altura;

    unsigned char **imagemLBP = criaImageLBP(largura - 2, altura - 2);
    if (!imagemLBP) {
        liberaPGM(img);
        return;
    }

    calculaLBP(img, imagemLBP);

    /*Salvar a imagem LBP*/
    FILE *arquivoSaida = fopen(imagemSaida, "wb");
    if (!arquivoSaida) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao criar o arquivo de saída %s\n", imagemSaida);
        /**/
        for (int i = 0; i < altura - 2; i++) {
            free(imagemLBP[i]);
        }
        free(imagemLBP);
        liberaPGM(img);
        return;
    }

    /*Escreve o cabecalho da imagem PGM*/
    fprintf(arquivoSaida, "P5\n%d %d\n255\n", largura - 2, altura - 2);

    /*Escreve os dados da imagem LBP*/
    for (int i = 0; i < altura - 2; i++) {
        fwrite(imagemLBP[i], sizeof(unsigned char), largura - 2, arquivoSaida);
    }

    fclose(arquivoSaida);
    liberaPGM(img);
    for (int i = 0; i < altura - 2; i++) {
        free(imagemLBP[i]);
    }
    free(imagemLBP);
}

/*Funcao para comparar duas imagens usando LBP*/
float comparaImagens(imagemPGM *img1, imagemPGM *img2) {
    float hist1[HISTOGRAM_SIZE];
    float hist2[HISTOGRAM_SIZE];
    unsigned char **lbp1 = criaImageLBP(img1->largura - 2, img1->altura - 2);
    unsigned char **lbp2 = criaImageLBP(img2->largura - 2, img2->altura - 2);

    if (!lbp1 || !lbp2) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao alocar memória para imagens LBP durante a comparação.\n");
        /**/
        if (lbp1) liberaImagemLBP(lbp1, img1->altura - 2);
        if (lbp2) liberaImagemLBP(lbp2, img2->altura - 2);
        return FLT_MAX; /*Retorna a maior distancia possivel em caso de erro*/
    }

    calculaLBP(img1, lbp1);
    calculaLBP(img2, lbp2);

    calculahistogramaLBP(lbp1, img1->largura - 2, img1->altura - 2, hist1);
    calculahistogramaLBP(lbp2, img2->largura - 2, img2->altura - 2, hist2);

    float distancia = distanciaEuclidiana(hist1, hist2, HISTOGRAM_SIZE);

    for (int i = 0; i < img1->altura - 2; i++) {
        free(lbp1[i]);
    }
    free(lbp1);

    for (int i = 0; i < img2->altura - 2; i++) {
        free(lbp2[i]);
    }
    free(lbp2);

    return distancia;
}