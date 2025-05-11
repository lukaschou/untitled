#include "intro.h"
#include "galaxy.h"

void init_game(GameContext *ctx) {
    generate_galaxy();
    ctx->current_game_state = STATE_PLAYING;
}
