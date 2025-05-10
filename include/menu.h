#ifndef MENU_HPP
#define MENU_HPP

// This needs to be in the order they are printed
typedef enum {
    NEWGAME = 1
} MenuOption;

void draw_menu(void);
long get_menu_opt(long max_opts);
void run_menu(void);
void handle_invalid_opt();
void execute_opt(long opt);

#endif
