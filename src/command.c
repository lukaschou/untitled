#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "galaxy.h"

struct CommandPair {
    const char *name;
    CommandFunc func;
};

void help_command(Command cmd) { printf("Help command was typed!\n"); }

struct CommandPair command_map[] = {
    {"help", help_command},
    {"map", c_map},
};

void execute_command(Command cmd) {
    if (cmd.argc == 0)
        return;
    for (int i = 0; command_map[i].name != NULL; i++) {
        if (strcmp(cmd.argv[0], command_map[i].name) == 0) {
            command_map[i].func(cmd);
            return;
        }
    }
    printf("%s", "No matching command found\n");
}

void parse_input(char *input, Command *cmd) {
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
        if (!(cmd->argv[cmd->argc++] = strdup(token))) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        // Ignore any arguments past our limit
        if (cmd->argc >= MAX_COMMAND_ARGS)
            break;
    }

    free(to_free); // Free copied input string
}

void free_command(Command *cmd) {
    if (cmd) {
        for (int i = 0; i < cmd->argc; i++) {
            free(cmd->argv[i]);
        }
    }
}
