#include "game_state.h"
#include "input.h"
#include "intro.h"
#include "menu.h" 
#include <stdio.h>

int main(void) {
    GameContext ctx = {STATE_MENU, 1};

    clear_screen();

    while (ctx.running) {
        switch (ctx.current_game_state) {
            case STATE_MENU:
                run_menu(&ctx);
            case STATE_INTRO:
                init_game(&ctx);
            case STATE_PLAYING:
                handle_user_input(&ctx);
        }
    }
}
