#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

struct Command {
    int argc;
    char **argv;
};

void clear_screen(void) { printf("\033[1;1H\033[2J"); }

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
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

void parse_input(char input[MAX_INPUT_SIZE]) {
    struct Command c;
    char *input_cpy = strdup(input);
    if (!input_cpy) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    char *to_free = input_cpy;
    char *argv[10]; // max args = 10
    char *token;
    int argc = 0;

    while ((token = strsep(&input_cpy, " "))) {
        if (*token == '\0')
            continue;
        argv[argc++] = token;
        if (argc >= 10) break;
    }

    for(int i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    free(to_free);
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    clear_screen();
    // Before main loop might want menu at some point (start game, etc.)
    while (1) {
        display_prompt();
        read_input(input);
        printf("%s", input);
        parse_input(input);
        // TODO: Execute command function
    }
}
