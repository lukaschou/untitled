CC = gcc

clicker: clicker.c
	$(CC) clicker.c -o clicker -Wall -Wextra -pedantic -std=c99
