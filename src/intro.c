#include "intro.h"
#include "galaxy.h"
#include "player.h"

void init_game(GameContext *ctx) {
    create_name(ctx);
    generate_galaxy(ctx);
    ctx->current_game_state = STATE_PLAYING;
}
