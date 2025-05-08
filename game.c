#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_COMMAND_ARGS 10

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
    
    // This trims the new line character so we don't have trailing space when parsing later
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
}

struct Command parse_input(char input[MAX_INPUT_SIZE]) {
    struct Command cmd;
    cmd.argc = 0;
    cmd.argv = malloc(sizeof(char *) * MAX_COMMAND_ARGS);
    if (!cmd.argv) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *input_cpy = strdup(input);
    if (!input_cpy) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    char *to_free = input_cpy;
    char *token;

    while ((token = strsep(&input_cpy, " "))) {
        if (*token == '\0')
            continue;

        cmd.argv[cmd.argc] = strdup(token);
        if (!cmd.argv[cmd.argc]) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        cmd.argc++;

        if (cmd.argc >= MAX_COMMAND_ARGS)
            break;
    }

    free(to_free);
    return cmd;
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    clear_screen();
    // Before main loop might want menu at some point (start game, etc.)
    while (1) {
        display_prompt();
        read_input(input);
        struct Command cmd = parse_input(input);

        printf("Argc: %d\n", cmd.argc);
        for (int i = 0; i < cmd.argc; i++) {
            printf("Argv[%d]: %s\n", i, cmd.argv[i]);
        }
        // TODO: Execute command function
    }
}
