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

Conjunto: Conjunto.o Ajuda.o Main.o 
		$(COMPILER) $(FLAGS) Conjunto.o Ajuda.o Main.o -lm -o Conjunto

Conjunto.o: Conjunto.c
		$(COMPILER) $(FLAGS) -c Conjunto.c

Ajuda.o: Ajuda.c
		$(COMPILER) $(FLAGS) -c Ajuda.c

Main.o: Main.c
		$(COMPILER) $(FLAGS) -c Main.c
clean: 
		rm *.o Conjunto
