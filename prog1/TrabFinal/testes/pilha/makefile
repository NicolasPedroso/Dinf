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
FLAGS = -g -Wall

Pilha: Pilha.o Main.o 
		$(COMPILER) $(FLAGS) Pilha.o Main.o -lm -o Pilha

Pilha.o: Pilha.c
		$(COMPILER) $(FLAGS) -c Pilha.c

Main.o: Main.c
		$(COMPILER) $(FLAGS) -c Main.c
clean: 
		rm *.o Pilha
