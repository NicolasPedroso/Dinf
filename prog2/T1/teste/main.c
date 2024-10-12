/*aqui*/
#include "pgm.h"
#include "lbp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s [-d <diretorio_base>] -i <imagem_teste> [-o <imagem_saida>]\n", argv[0]);
        return 1;
    }

    const char *baseDir = NULL;
    const char *imagemTeste = NULL;
    const char *imagemSaida = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            baseDir = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            imagemTeste = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            imagemSaida = argv[++i];
        }
    }

    if (!imagemTeste) {
        fprintf(stderr, "Imagem de teste é obrigatória.\n");
        fprintf(stderr, "Uso: %s [-d <diretorio_base>] -i <imagem_teste> [-o <imagem_saida>]\n", argv[0]);
        return 1;
    }

    if (baseDir) {
        comparaBase(baseDir, imagemTeste);
    }

    if (imagemSaida) {
        geraimagemLBP(imagemTeste, imagemSaida);
    }

    return 0;
}
