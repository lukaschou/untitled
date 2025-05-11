#ifndef HEADER_H
#define HEADER_H

#include "game_state.h"

#define MAX_INPUT_SIZE 1024

char *trim_whitespace(char *str);
void display_prompt(void);
void clear_screen(void);
int read_input(char *input, int max_size);
void handle_user_input(GameContext *ctx);

#endif
