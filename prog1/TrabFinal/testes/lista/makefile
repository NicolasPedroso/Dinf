parametrosCompilacao=-Wall #-Wshadow
nomePrograma=trab5

all: $(nomePrograma)

$(nomePrograma): testa_lista.o listaDupla.o
	gcc -o $(nomePrograma) testa_lista.o listaDupla.o $(parametrosCompilacao)

testa_lista.o: testa_lista.c
	gcc -c testa_lista.c $(parametrosCompilacao)

listaDupla.o: listaDupla.h listaDupla.c
	gcc -c listaDupla.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)