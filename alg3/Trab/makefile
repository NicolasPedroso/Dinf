CC = gcc
CFLAGS = -Wall -g

all: dicionario

dicionario: main.o dicionario.o
	$(CC) $(CFLAGS) -o dicionario main.o dicionario.o

main.o: main.c dicionario.h
	$(CC) $(CFLAGS) -c main.c

dicionario.o: dicionario.c dicionario.h
	$(CC) $(CFLAGS) -c dicionario.c

clean:
	rm -f *.o dicionario
