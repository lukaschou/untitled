#include "term_util.h"
#include "input.h"
#include <termios.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>

static struct termios original;

void disable_echo() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void enable_echo() {
    tcsetattr(STDERR_FILENO, TCSANOW, &original);
}

/* Use this when we actually need to flush stdin, not when
 * we are writing to a buffer into stdin (like fgets)
 * */
void flush_stdin() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    char buf[MAX_INPUT_SIZE];
    while (read(STDIN_FILENO, buf, sizeof(buf)) > 0) {
        ;
    }

    fcntl(STDIN_FILENO, F_SETFL, flags);
}
