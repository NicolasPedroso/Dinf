CC = gcc
CFLAGS = -Wall -O2 -pthread

OBJ = main.o barreira.o fila_fifo.o

all: trabalho1a

trabalho1a: $(OBJ)
	$(CC) -o $@ $(OBJ) -lrt

clean:
	rm -f *.o trabalho1a
