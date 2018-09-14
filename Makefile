all: automaton

FLAGS = -Wall -std=c11 -ggdb

automaton: automaton.c
	gcc $(FLAGS) -o automaton automaton.c

