#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct termios og_termios;

void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_termios) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

void enable_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &og_termios) == -1) {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
    atexit(disable_raw_mode);

    struct termios raw = og_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

int main() {
    enable_raw_mode();
    char c;
    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }
    return EXIT_SUCCESS;
}
