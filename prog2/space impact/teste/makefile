TARGET = AS
SOURCES = Space\ Impact.c Jogador.c Inimigos.c Controle.c Bala.c Pistola.c
ALLEGRO_FLAGS = $(shell pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_ttf-5)

all:
	gcc $(SOURCES) -o $(TARGET) $(ALLEGRO_FLAGS)
