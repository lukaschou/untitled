#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

#define MAX_INPUT_SIZE 1024
#define MAX_COMMAND_ARGS 10

struct Command {
    int argc;
    char *argv[MAX_COMMAND_ARGS];
};

/* TEST COMMAND MAPPING */
typedef void (*CommandFunc)(struct Command cmd);
struct CommandPair {
    const char* name;
    CommandFunc func;
};

void help_command(struct Command cmd) {
    printf("Help command was typed!\n");
}

struct CommandPair command_map[] = {
    {"help", help_command},
    {NULL, NULL}
};

void execute_command(struct Command cmd) {
    if (cmd.argc == 0) return;
    for (int i = 0; command_map[i].name != NULL; i++) {
        if (strcmp(cmd.argv[0], command_map[i].name) == 0) {
            command_map[i].func(cmd);
            return;
        }
    }
    printf("%s", "No matching command found\n");
}
/* END TEST COMMAND MAPPING*/

void parse_input(char input[MAX_INPUT_SIZE], struct Command *cmd) {
    cmd->argc = 0; // Reset arg count

    char *input_cpy = strdup(input);
    if (!input_cpy) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    char *to_free = input_cpy;
    char *token;
    while ((token = strsep(&input_cpy, " \t\n"))) {
        // Skip empty fields (multiple delims in a row)
        if (*token == '\0')
            continue;
        // Copy our arg into the struct and increment count
        if(!(cmd->argv[cmd->argc++] = strdup(token))) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        // Ignore any arguments past our limit
        if (cmd->argc >= MAX_COMMAND_ARGS)
            break;
    }

    free(to_free); // Free copied input string
}

void free_command(struct Command *cmd) {
    if (cmd) {
        for (int i = 0; i < cmd->argc; i++) {
            free(cmd->argv[i]);
        }
    }
}

// Idea - map that maps commands to function references for execution
//
int main(void) {
    struct Command cmd;
    char input[MAX_INPUT_SIZE];
    clear_screen();
    // Before main loop might want menu at some point (start game, etc.)
    while (1) {
        display_prompt();
        read_input(input);
        parse_input(input, &cmd);
        execute_command(cmd);
        free_command(&cmd);
    }
}
