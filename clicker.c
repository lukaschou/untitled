#include <sys/resource.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct termios og_termios; // User's original terminal config

/* Clears screen, perrors with a given string and exits the program */
void die(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}

/* Reset terminal flags to original config */
void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios) == -1)
        die("tcsetattr");
}

/* Saves user's original terminal config and converts to raw mode */
void enable_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &og_termios) == -1) 
        die("tcgetattr");
    if (atexit(disable_raw_mode) != 0) {
         /* Manually exit because atexit does not set errno on failure */
        fprintf(stderr, "atexit: cannot set exit function\n");
        exit(EXIT_FAILURE);
    }

    struct termios raw = og_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
        die("tcsetattr");
}

/*
 * Read bytes one at a time from standard input
 * Will need to handle multi-byte keypresses like arrowkeys
 */
int readKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1) die("read");
    }
    return c;
}

void processKeyPress() {
    char c = readKey();

    switch (c) {
        case 'q':
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("CHAR: %d\r\n", c);
    }
}

/* 
 * Clear screen and reposition cursor to top-left corner.
 * We should make sure to call this whenever we exit too (die, quit, etc...)
 * Also error handling
 */
void refreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

int main() {
    enable_raw_mode();
    refreshScreen();
    while (1) {
        processKeyPress();
    }
    printf("Exiting program...");
    return EXIT_SUCCESS;
}
