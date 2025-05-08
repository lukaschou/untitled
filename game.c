#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_COMMAND_ARGS 10

struct Command {
    int argc;
    char **argv;
};
/* TEST COMMAND MAPPING */
typedef void (*CommandFunc)(struct Command *cmd);
struct CommandPair {
    const char* name;
    CommandFunc func;
};

void help_command(struct Command *cmd) {
    printf("Help command was typed!\n");
}

struct CommandPair command_map[] = {
    {"help", help_command},
    {NULL, NULL}
};

void execute_command(struct Command *cmd) {
    if (cmd->argc == 0) return;
    for (int i = 0; command_map[i].name != NULL; i++) {
        if (strcmp(cmd->argv[0], command_map[i].name) == 0) {
            command_map[i].func(cmd);
            return;
        }
    }
    printf("%s", "No matching command found");
}
/* END TEST COMMAND MAPPING*/

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

// Command must be freed after use (struct and argv)
// Made this a pointer to show that it needs to be free
// But it's small enough it might not matter
// Just would be hard to remember that argv and its elements must be freed as well
struct Command* parse_input(char input[MAX_INPUT_SIZE]) {
    struct Command *cmd = malloc(sizeof(struct Command));
    if (!cmd) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    cmd->argc = 0;
    cmd->argv = malloc(sizeof(char *) * MAX_COMMAND_ARGS);
    if (!cmd->argv) {
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

        cmd->argv[cmd->argc] = strdup(token);
        if (!cmd->argv[cmd->argc]) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        cmd->argc++;

        if (cmd->argc >= MAX_COMMAND_ARGS)
            break;
    }

    free(to_free);
    return cmd;
}

void free_command(struct Command *cmd) {
    if (cmd) {
        for (int i = 0; i < cmd->argc; i++) {
            free(cmd->argv[i]);
        }
        free(cmd->argv);
        free(cmd);
    }
}

// Idea - map that maps commands to function references for execution
//
int main(void) {
    char input[MAX_INPUT_SIZE];
    clear_screen();
    // Before main loop might want menu at some point (start game, etc.)
    while (1) {
        display_prompt();
        read_input(input);
        struct Command *cmd = parse_input(input);

        printf("Argc: %d\n", cmd->argc);
        for (int i = 0; i < cmd->argc; i++) {
            printf("Argv[%d]: %s\n", i, cmd->argv[i]);
        }
        execute_command(cmd);
        free_command(cmd);
    }
}
