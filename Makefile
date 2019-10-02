all: $(wildcard *.c)  $(wildcard *.h)
	gcc -g MAIN.c
