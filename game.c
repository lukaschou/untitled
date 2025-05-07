#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 5

void clear_screen(void) {
#ifdef _WIN32 // This will need testing unless we don't want to care about windows
    sytem("cls");
#else
    system("clear");
#endif
}

void display_prompt(void) {
    printf("> ");
}

void read_input(char input[MAX_INPUT_SIZE]) {
    if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
        if (feof(stdin)) {
            // Ignore EOF char
            clearerr(stdin);
        } else {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
    }

    // Ignore overflowed data
    int len = strlen(input);
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
