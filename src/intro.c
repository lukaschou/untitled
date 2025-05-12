#include "intro.h"
#include "input.h"
#include "galaxy.h"
#include "player.h"
#include "term_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void init_game(GameContext *ctx) {
    create_name(ctx);
    generate_galaxy(ctx);
    write_intro_text(ctx);
    ctx->current_game_state = STATE_PLAYING;
}

void write_intro_text(GameContext *ctx) {
    disable_echo();
    clear_screen();
    typewriter_text_effect("[INITIALIZING]\n", 50000);
    usleep(1000000);
    printf("[BOOT SYSTEM COMPLETE]\n\n");
    usleep(600000);
    printf("STARHAUL LOGISTICS INTERFACE v4.9.17\n");
    usleep(400000);
    printf("USER | %s\n", ctx->player.name);
    flush_stdin();
    enable_echo();
}

void typewriter_text_effect(const char *str, int delay) {
    if (str == NULL) {
        return;
    }
    
    srand(time(NULL));

    while (*str) {
        printf("%c", *str++);

        int noise = (rand() % (2 * 10000 + 1) - 10000);
        usleep(delay + noise);
        if (fflush(stdout) == EOF) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }
    }
}
