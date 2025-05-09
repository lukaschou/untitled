#ifndef HEADER_H
#define HEADER_H

#include "game_state.h"

#define MAX_INPUT_SIZE 1024

void display_prompt(void);
void clear_screen(void);
void read_input(char input[MAX_INPUT_SIZE]);
void handle_user_input(GameContext *ctx);

#endif
