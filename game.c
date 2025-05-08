#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "command.h"

// Idea - map that maps commands to function references for execution
//
int main(void) {
    Command cmd;
    char input[MAX_INPUT_SIZE];
    clear_screen();
    // Before main loop might want menu at some point (start game, etc.)
    while (1) {
        display_prompt();
        read_input(input);
        parse_input(input, &cmd);
        execute_command(cmd);
        free_command(&cmd);
    }
}
