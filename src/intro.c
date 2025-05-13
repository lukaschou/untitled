#include "intro.h"
#include "galaxy.h"
#include "input.h"
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

    typewriter_text_effect("[INITIALIZING SYSTEM]\n", 50000);
    usleep(1000000);
    typewriter_text_effect("[BOOT SEQUENCE COMPLETE]\n\n", 40000);
    usleep(95000);
    typewriter_text_effect("STARHAUL LOGISTICS INTERFACE v4.9.17\n", 40000);
    typewriter_text_effect("WELCOME ", 30000);
    typewriter_text_effect(ctx->player.name, 30000);
    printf("\n\n");
    usleep(1000000);
    typewriter_text_effect("INCOMING TRANSMISSION FROM [UCC-0013028A]\n\n",
                           30000);

    usleep(1000000);
    typewriter_text_effect("[\033[1mBEGIN TRANSMISSION\033[0m]\n\n", 40000);

    typewriter_text_effect("\033[1mACCOUNT:\033[0m 9X-773-ZA\n", 40000);
    typewriter_text_effect("\033[1mDEBTOR: \033[0m", 40000);
    typewriter_text_effect(ctx->player.name, 40000);
    typewriter_text_effect("\n\033[1mBALANCE DUE:\033[0m 425,000 Credits\n",
                           40000);
    typewriter_text_effect("\033[1mDEADLINE:\033[0m 30 Cycles\n\n", 40000);

    typewriter_text_effect(
        "\033[1mFINAL NOTICE OF IMMINENT ASSET SEIZURE\033[0m\n\n", 30000);

    typewriter_text_effect(
        "This is an automated transmission issued by [collections agency] on "
        "behalf of [bank] regarding your outstanding financial obligation.\n\n"
        "As of now, your account has been classified as "
        "\033[1mdelinquent\033[0m. "
        "Current balance due: 425,000 Credits.\nFailure to satisfy this debt "
        "within 30 cycles will result in your account being placed in "
        "\033[1mdefault\033[0m.\n\n"
        "If your balance is not settled within the specified window, the "
        "following actions may be taken with or without notice:\n\n"
        "\t> Seizure of all registered assets, including but not limited to "
        "vessels, property, and fuel reserves\n\n"
        "If the total assessed value of seized assets does not exceed your "
        "outstanding balance, your debt may be sold to a third party."
        "\nIn such cases, you may be contractually obliged to enter a "
        "compulsory labor arrangement until the outstanding debt is resolved "
        "in full.\n\n"
        "While your account is delinquent [bank] has been authorized to seize "
        "50% of all credits earned through your shipping operations until your "
        "outstanding balance has been settled.\n\n",
        10000
    );

    usleep(100000);
    typewriter_text_effect("[\033[1mEND TRANSMISSION\033[0m]\n\n", 40000);

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
        usleep(delay);
        if (fflush(stdout) == EOF) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }
    }
}
