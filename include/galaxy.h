#ifndef GALAXY_H
#define GALAXY_H

#include "game_state.h"
#include "command.h"

#define MAP_SIZE 20

typedef struct {
    const char* name;
    int coord[2];
} Planet;

void c_map(Command cmd, GameContext *ctx);
void generate_galaxy();

#endif
