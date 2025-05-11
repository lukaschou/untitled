#ifndef GAME_STATE_H
#define GAME_STATE_H

#define MAP_SIZE 20
#define MAX_NAME_SIZE 15

typedef struct {
    const char* name;
    int coord[2];
} Planet;

typedef struct {
    char name[MAX_NAME_SIZE];
    int home_planet_coords[2];
} Player;

typedef enum {
    STATE_MENU,
    STATE_INTRO,
    STATE_PLAYING,
} GameState;

typedef struct {
    GameState current_game_state;
    Planet *galaxy[MAP_SIZE][MAP_SIZE];
    Player player;
    int running;
} GameContext;

#endif
