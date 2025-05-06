#include <stdio.h>
#include <unistd.h>

int main() {
    printf("\033[H\033[2J\033[?25l"); // Clear screen and disable cursor
    fflush(stdout);
    sleep(3);
    printf("\033[?25h");
}
