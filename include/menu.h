#ifndef MENU_HPP
#define MENU_HPP

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "input.h"

// This needs to be in the order they are printed
typedef enum {
    NEWGAME = 1
} MenuOption;

void draw_menu(void);
long get_menu_option();
void run_menu(void);
void handle_invalid_opt(char *val);
int execute_opt(long opt);

#endif
