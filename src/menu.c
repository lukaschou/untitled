#include "menu.h"
#include "input.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prints introduction text and lists menu options */
void draw_menu(void) {
    printf("Welcome to \033[1mSpace Freight\033[22m\n\n");
    printf("1. New Game\n");
    printf("\n");
    if (fflush(stdout)) {
        perror("fflush");
        exit(EXIT_FAILURE);
    }
}

/*
 * Gets input from a user until ONLY a valid menu option number is input.
 * Returns a long because strtol does, and who cares. If an invalid
 * value is received, clears the screen and displays the menu and prompt.
 */
long get_menu_opt() {
    char input[MAX_INPUT_SIZE];
    long value = 0;
    int success;
    do {
        success = 1;
        char *endptr = NULL;
        printf("Enter option: ");

        read_input(input, MAX_INPUT_SIZE);
        input[strcspn(input, "\n")] = '\0'; // strip newline
        errno = 0;
        value = strtol(input, &endptr, 10);
        if (errno || input[0] == '\0' || endptr[0] != '\0'
            || value < 1 || value > MAX_OPTS) {
            success = 0;
            handle_invalid_opt();
        }
    } while (!success);

    return value;
}

void handle_invalid_opt() {
    printf("Invalid option\n");
    printf("Press Enter to continue\n");

    char c;
    do {
        c = fgetc(stdin);
        if (c == EOF) {
            if (feof(stdin)) {
                clearerr(stdin);
                c = 'p';
            } else {
                perror("fgetc");
                exit(EXIT_FAILURE);
            }
        }
    } while (c != '\n');
    clear_screen();
    draw_menu();
}

/* Executes a menu option. Option MUST be valid */
void execute_opt(long opt, GameContext *ctx) {
    switch (opt) {
        case NEWGAME:
            ctx->current_game_state = STATE_INTRO;
            break;
    }
}

void run_menu(GameContext *ctx) {
    draw_menu();
    execute_opt(get_menu_opt(), ctx);
}
