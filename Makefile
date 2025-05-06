CC = gcc

game: game.c
	$(CC) game.c -o game -Wall -Wextra -pedantic -std=c99
