#ifndef MENU_HPP
#define MENU_HPP

#include "game_state.h"

#define MAX_OPTS 1

// This needs to be in the order they are printed
typedef enum {
    NEWGAME = 1
} MenuOption;

void draw_menu(void);
long get_menu_opt();
void run_menu(GameContext *ctx);
void handle_invalid_opt();
void execute_opt(long opt, GameContext *ctx);

#endif
