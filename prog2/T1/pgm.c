#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Funcao para pular comentarios no arquivo PGM*/
void pulaComentario(FILE *file) {
    int ch;
    char linha[1000];
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            continue;
        }
        if (ch == '#') {
            if (fgets(linha, sizeof(linha), file) == NULL) {
                break;
            }
        } else {
            ungetc(ch, file);
            break;
        }
    }
}

/*Função para ler uma imagem PGM (P2 ou P5)*/
imagemPGM* lerPGM(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        /**/
        return NULL;
    }

    imagemPGM *img = (imagemPGM*)malloc(sizeof(imagemPGM));
    if (!img) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        /**/
        fclose(file);
        return NULL;
    }

    /*Le o formato da imagem*/
    if (fscanf(file, "%2s", img->formato) != 1) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao ler o formato da imagem em %s\n", filename);
        /**/
        free(img);
        fclose(file);
        return NULL;
    }

    /*Verifica se o formato eh P2 ou P5*/
    if (strcmp(img->formato, "P2") != 0 && strcmp(img->formato, "P5") != 0) {
        /*Debugging print*/
        fprintf(stderr, "Formato de imagem inválido (%s) em %s! Apenas P2 e P5 são suportados.\n", img->formato, filename);
        /**/
        free(img);
        fclose(file);
        return NULL;
    }

    /*Pula caracteres de comentario e le a largura e altura*/
    pulaComentario(file);
    if (fscanf(file, "%d %d", &img->largura, &img->altura) != 2 || img->largura <= 0 || img->altura <= 0) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao ler a largura e altura da imagem em %s\n", filename);
        /**/
        free(img);
        fclose(file);
        return NULL;
    }

    /*Pula caracteres de comentario e le o valor maximo de cinza*/
    pulaComentario(file);
    if (fscanf(file, "%d", &img->maxVal) != 1) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao ler o valor máximo de cinza em %s\n", filename);
        
        free(img);
        fclose(file);
        return NULL;
    }

    fgetc(file); /*Pula o caractere de nova linha apos o cabecalho*/

    /*Aloca memoria para os pixels*/
    img->pixels = (unsigned char **)malloc(img->altura * sizeof(unsigned char *));
    if (!img->pixels) {
        /*Debugging print*/
        fprintf(stderr, "Erro ao alocar memória para os pixels.\n");
        /**/
        free(img);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < img->altura; i++) {
        img->pixels[i] = (unsigned char *)malloc(img->largura * sizeof(unsigned char));
        if (!img->pixels[i]) {
            /*Debugging print*/
            fprintf(stderr, "Erro ao alocar memória para a linha %d dos pixels.\n", i);
            /**/
            for (int k = 0; k < i; k++) free(img->pixels[k]);
            free(img->pixels);
            free(img);
            fclose(file);
            return NULL;
        }
    }

    /*Le os dados da imagem com base no formato*/
    if (strcmp(img->formato, "P2") == 0) {
        /*Formato P2*/
        for (int i = 0; i < img->altura; i++) {
            for (int j = 0; j < img->largura; j++) {
                int pixel;
                if (fscanf(file, "%d", &pixel) != 1) {
                    /*Debugging print*/
                    fprintf(stderr, "Erro ao ler o pixel (%d, %d) em %s\n", i, j, filename);
                    /**/
                    for (int k = 0; k <= i; k++) free(img->pixels[k]);
                    free(img->pixels);
                    free(img);
                    fclose(file);
                    return NULL;
                }
                if (pixel < 0 || pixel > img->maxVal) {
                    /*Debugging print*/
                    fprintf(stderr, "Valor de pixel inválido (%d) em (%d, %d) em %s\n", pixel, i, j, filename);
                    /**/
                    for (int k = 0; k <= i; k++) free(img->pixels[k]);
                    free(img->pixels);
                    free(img);
                    fclose(file);
                    return NULL;
                }
                img->pixels[i][j] = (unsigned char)pixel;
            }
        }
    } else {
        /*Formato P5*/
        for (int i = 0; i < img->altura; i++) {
            if (fread(img->pixels[i], sizeof(unsigned char), img->largura, file) != (size_t)img->largura) {
                /*Debugging print*/
                fprintf(stderr, "Erro ao ler os pixels binários na linha %d em %s\n", i, filename);
                /**/
                for (int k = 0; k <= i; k++) free(img->pixels[k]);
                free(img->pixels);
                free(img);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return img;
}

/*Funçao para liberar a memoria da imagem*/
void liberaPGM(imagemPGM *img) {
    if (img) {
        if (img->pixels) {
            for (int i = 0; i < img->altura; i++) {
                free(img->pixels[i]);
            }
            free(img->pixels);
        }
        free(img);
    }
}