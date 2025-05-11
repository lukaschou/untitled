#include "player.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

void create_name(GameContext *ctx) {
    int status;
    char name_input[MAX_NAME_SIZE];
    char *trimmed_name;
    do {
        printf("Enter your name: ");
        status = read_input(name_input, MAX_NAME_SIZE);
        if (status == -1) {
            printf("Character limit for name (%d) exceeded\n", MAX_NAME_SIZE-1);
        }
        trimmed_name = trim_whitespace(name_input);
        if (!strlen(trimmed_name)) {
            printf("Please input an alphabetic name\n");
            status = -1;
        }
    } while (status <= 0);

    // Null home planet for now...
    strcpy(ctx->player.name, trimmed_name);
    printf("You are \033[1m%s\033[0m\n", ctx->player.name);
}