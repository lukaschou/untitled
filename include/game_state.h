#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    STATE_PLAYING,
} GameState;

typedef struct {
    GameState current_game_state;
    int running;
} GameContext;

#endif
