#ifndef PGM_H
#define PGM_H

typedef struct {
    char formato[3];
    int largura;    
    int altura;     
    int maxVal;     
    unsigned char **pixels;
} imagemPGM;

/*Funcao para ler uma imagem PGM*/
imagemPGM* lerPGM(const char *filename);

/*Funcao para liberar a memoria alocada para uma imagem PGM*/
void liberaPGM(imagemPGM *img);

#endif