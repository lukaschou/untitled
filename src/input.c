#include "input.h"
#include "command.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen(void) { printf("\033[1;1H\033[2J"); }

void display_prompt(void) {
    printf("> ");
    if (fflush(stdout)) {
        perror("fflush");
        exit(EXIT_FAILURE);
    }
}

/*
 * Reads max_size chars from stdin into input. If
 * more than max_size chars are read, -1 is returned.
 */
int read_input(char *input, int max_size) {
    if (!fgets(input, max_size, stdin)) {
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
        return 0;
    }

    int len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return len;
}

void handle_user_input(GameContext *ctx) {
    Command cmd;
    char input[MAX_INPUT_SIZE];

    display_prompt();
    int err = read_input(input, MAX_INPUT_SIZE);

    if (err == 0) {
        return;
    }

    if (err == -1) {
        return;
    }

    parse_input(input, &cmd);
    execute_command(cmd, ctx);
    free_command(&cmd);
}

/*
 * Note: This function returns a pointer to a substring of the original string.
 * If the given string was allocated dynamically, the caller must not overwrite
 * that pointer with the returned value, since the original pointer must be
 * deallocated using the same allocator with which it was allocated.  The return
 * value must NOT be deallocated using free() etc.
 */
char *trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}
