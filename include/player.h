#ifndef PLAYER_H
#define PLAYER_H

#include "galaxy.h"

#define MAX_NAME_SIZE 15

typedef struct {
  char name[MAX_NAME_SIZE];
  Planet *home_planet;
} Player;

void create_name();

#endif