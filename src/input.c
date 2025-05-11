#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "command.h"

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
        if (!feof(stdin)) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }
    }

    if (feof(stdin)) {
        clearerr(stdin);
        printf("\n");
        input[0] = '\0';
        if (fflush(stdout)) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }
        return;
    }
    int len = strlen(input);
    // Ignore overflowed data
    if (len > 0 && input[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // blah blah blah
    }    
}

void handle_user_input(GameContext *ctx) {
    Command cmd;
    char input[MAX_INPUT_SIZE];

    display_prompt();
    read_input(input);
    parse_input(input, &cmd);
    execute_command(cmd, ctx);
    free_command(&cmd);
}
