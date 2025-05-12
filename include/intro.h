#ifndef INTRO_H
#define INTRO_H

#include "game_state.h"

void init_game(GameContext *ctx);
void write_intro_text(GameContext *ctx);
void typewriter_text_effect(const char *str, int delay);

#endif
