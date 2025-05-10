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
    printf("2. Continue\n");
    printf("3. Settings\n\n");
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
long get_menu_opt(long max_opts) {
    char input[MAX_INPUT_SIZE];
    long value = 0;
    int success;
    do {
        success = 1;
        char *endptr = NULL;
        printf("Enter option: ");

        read_input(input);
        input[strcspn(input, "\n")] = '\0'; // strip newline
        errno = 0;
        value = strtol(input, &endptr, 10);
        if (errno || input[0] == '\0' || endptr[0] != '\0'
            || value < 0 || value > max_opts) {
            success = 0;
            handle_invalid_opt();
        }
        if (fflush(stdout)) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }
    } while (!success);

    return value;
}

void handle_invalid_opt() {
    printf("Invalid option\n");
    printf("Press Enter to continue\n");
    if (fflush(stdout)) {
        perror("fflush");
        exit(EXIT_FAILURE);
    }

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
void execute_opt(long opt) {
    switch (opt) {
        case NEWGAME:
            printf("New game selected...\n");
            break;
    }
}

void run_menu(void) {
    draw_menu();
    execute_opt(get_menu_opt(1));
}
