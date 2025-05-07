#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void clear_screen(void) {
    printf("\033[1;1H\033[2J");
}

void display_prompt(void) {
    printf("> ");
    if (fflush(stdout)) {
        perror("fflush");
        exit(EXIT_FAILURE);
    }
}

void read_input(char input[MAX_INPUT_SIZE]) {
    if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
        if (feof(stdin)) {
            // Ignore EOF char
            clearerr(stdin);
            printf("\n");
            fflush(stdout);
            return;
        } else {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
    }

    int len = strlen(input);
    // Ignore overflowed data
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    clear_screen();
    // Before main loop might want menu at some point (start game, etc.)
    while(1) {
        display_prompt();
        read_input(input);
        // TODO: Execute command function
    }
}
