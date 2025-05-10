#include "menu.h"
#include "input.h"
#include <string.h>

/* Prints introduction text and lists menu options */
void draw_menu(void) {
    printf("Welcome to Space Freight\n\n");
    printf("1. New Game\n");
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
    int success = 1;
    do {
        char *endptr = NULL;
        printf("Enter option: ");
        read_input(input);
        input[strcspn(input, "\n")] = '\0'; // strip newline
        errno = 0;
        value = strtol(input, &endptr, 10);
        if (errno || input[0] == '\0' || endptr[0] != '\0') {
            success = 0;
            handle_invalid_opt(input);
        }
        if (fflush(stdout)) {
            perror("fflush");
            exit(EXIT_FAILURE);
        }
    } while (!success);

    return value;
}

void handle_invalid_opt(char *val) {
    printf("Invalid option: %s\n", val); 
    printf("Press any key to continue\n");
    if (fflush(stdout)) {
        perror("fflush");
        exit(EXIT_FAILURE);
    }
    fgetc(stdin);
    clear_screen();
    draw_menu();
}

int execute_opt(long opt) {
   switch (opt) {
       case NEWGAME:
           printf("New game selected...\n");
           return 0;
        default: {
           char opt_str[30]; // Enough to hold a long string
           snprintf(opt_str, 30, "%ld", opt);
           handle_invalid_opt(opt_str);
           return -1;
        }
    } 
}

void run_menu(void) {
    draw_menu();
    int err_status;
    do {
        err_status = execute_opt(get_menu_opt());
    } while (err_status);
}
