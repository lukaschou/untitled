#include "command.h"
#include "game_state.h"
#include "input.h"

int main(void) {
    GameContext ctx = {STATE_PLAYING, 1};

    Command cmd;
    char input[MAX_INPUT_SIZE];
    clear_screen();

    while (ctx.running) {
        switch (ctx.current_game_state) {
        case STATE_PLAYING:

            display_prompt();
            read_input(input);
            parse_input(input, &cmd);
            execute_command(cmd);
            free_command(&cmd);
        }
    }
}
