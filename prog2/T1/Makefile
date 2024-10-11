CC     = gcc
CFLAGS = -std=c11 -Wall

EXEC = LBP
SRC = lbp.c

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) -lm

clean:
	rm -f $(EXEC)
