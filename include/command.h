#ifndef COMMAND_H
#define COMMAND_H

#include "game_state.h"

#define MAX_COMMAND_ARGS 10

typedef struct {
    int argc;
    char *argv[MAX_COMMAND_ARGS];
} Command;

typedef void (*CommandFunc)(Command cmd, GameContext *ctx);

void parse_input(char *input, Command *cmd);
void free_command(Command *cmd);
void execute_command(Command cmd, GameContext *ctx);
void c_exit(Command cmd, GameContext *ctx);
void c_help(Command cmd, GameContext *ctx);


#endif
