CC=g++
CFLAGS=-I.

lox: lox.o token.o
	$(CC) -o lox lox.o token.o

