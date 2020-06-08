#include "../inc/ush.h"

int mx_get_twidth(void) {
    int col = 0;
    int success = 0;

    success = tgetent(NULL, "xterm-256color");
    if (success < 0) {
        fprintf(stderr, "%s", MX_ETGTN);
        exit(1);
    }
    col = tgetnum("co");
    return col;
}
