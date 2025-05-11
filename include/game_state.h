#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    STATE_MENU,
    STATE_INTRO,
    STATE_PLAYING,
} GameState;

typedef struct {
    GameState current_game_state;
    int running;
} GameContext;

#endif
