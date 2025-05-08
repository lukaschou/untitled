#ifndef COMMAND_H
#define COMMAND_H

#define MAX_COMMAND_ARGS 10

typedef struct {
    int argc;
    char *argv[MAX_COMMAND_ARGS];
} Command;

typedef void (*CommandFunc)(Command cmd);

void parse_input(char input[MAX_COMMAND_ARGS], Command *cmd);
void free_command(Command *cmd);
void execute_command(Command cmd);
void help_command(Command cmd);

#endif
