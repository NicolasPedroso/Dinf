#Nicoals Gabriel Ramos Pedroso GRR20204019

CC = gcc
CFLAGS = -std=c11 -Wall
LIBS = -lm

TARGET = LBP
OBJS = main.o pgm.o lbp.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c pgm.h lbp.h
	$(CC) $(CFLAGS) -c main.c

pgm.o: pgm.c pgm.h
	$(CC) $(CFLAGS) -c pgm.c

lbp.o: lbp.c lbp.h pgm.h
	$(CC) $(CFLAGS) -c lbp.c

clean:
	rm -f $(TARGET) $(OBJS)
