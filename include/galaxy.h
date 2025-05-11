#ifndef GALAXY_H
#define GALAXY_H

#include "game_state.h"
#include "command.h"

void c_map(Command cmd, GameContext *ctx);
void generate_galaxy(GameContext *ctx);

#endif
