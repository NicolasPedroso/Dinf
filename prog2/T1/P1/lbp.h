#ifndef LBP_H
#define LBP_H

#include "pgm.h"

#define HISTOGRAM_SIZE 256

/*Funcao para alocar a imagem LBP*/
unsigned char** criaImageLBP(int largura, int altura);

/*Funcao para liberar a imagem LBP*/
void liberaImagemLBP(unsigned char **imagemlbp, int altura);

/*Funcao para calcular o LBP de uma imagem*/
void calculaLBP(imagemPGM *img, unsigned char **imagemLBP);

/*Funcao para calcular o histograma LBP de uma imagem*/
void calculahistogramaLBP(unsigned char **imagemLBP, int largura, int altura, float *histograma);

/*Funcao para calcular a distancia Euclidiana entre dois histogramas*/
float distanciaEuclidiana(float *hist1, float *hist2, int tam);

/*Funcao para comparar uma imagem de teste com todas as imagens da base*/
void comparaBase(const char *baseDir, const char *imagemTeste);

/*Funcao para gerar uma imagem LBP a partir de uma imagem de entrada*/
void geraimagemLBP(const char *imagemEntrada, const char *imagemSaida);

/*Funcao para comparar duas imagens usando LBP*/
float comparaImagens(imagemPGM *img1, imagemPGM *img2);

/*Funcao para calcular a mediana*/
void calculaMediana(imagemPGM *img, unsigned char **imagemLBP);

/*Funcao para gerar uma imagem com a media a partir de uma imagem de entrada*/
void mediana(const char *imagemEntrada, const char *imagemSaida);

#endif