#include "game_state.h"
#include "input.h"

int main(void) {
    GameContext ctx = {STATE_PLAYING, 1};

    clear_screen();

    while (ctx.running) {
        switch (ctx.current_game_state) {
        case STATE_PLAYING:
            handle_user_input(&ctx);
        }
    }
}
