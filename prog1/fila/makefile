SHELL = /bin/sh
#
# 
#
# Variavel com o nome do compilador utilizado pelo makefile
COMPILER = gcc
# Flags que vão ser utilizadas pelo compilador
# -g		Para trazer informação de debug com a compilação
# -Wall		Traz os warnigs de maneira verbosa
# -std=c90	Para utilizar a linguagem C90 na compilação
FLAGS = -g -std=c90 -Wall

Fila: Fila.o Main.o 
		$(COMPILER) $(FLAGS) Fila.o Main.o -lm -o filaTeste

Fila.o: Fila.c
		$(COMPILER) $(FLAGS) -c Fila.c

Main.o: Main.c
		$(COMPILER) $(FLAGS) -c Main.c

clean: 
		rm *.o filaTeste
