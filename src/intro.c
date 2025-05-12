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
    
    typewriter_text_effect("[INITIALIZING SYSTEM...]\n", 50000);
    usleep(100000);
    typewriter_text_effect("[BOOT SEQUENCE COMPLETE]\n\n", 40000);
    usleep(95000);
    typewriter_text_effect("STARHAUL LOGISTICS INTERFACE v4.9.17\n", 3500);
    typewriter_text_effect("WELCOME ", 30000);
    typewriter_text_effect(ctx->player.name, 30000);
    printf("\n");

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
        int jitter = 100000;
        int variation = abs(rand() % (2 * jitter + 1) - jitter);
        usleep(delay + variation);
        if (fflush(stdout) == EOF) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }
    }
}
