#ifndef GALAXY_H
#define GALAXY_H

#include "command.h"

#define MAP_SIZE 20

typedef struct {
    const char* name;
    int coord[2];
} Planet;

void c_map(Command cmd);
void generate_galaxy();

#endif
