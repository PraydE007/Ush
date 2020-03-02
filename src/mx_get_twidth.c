#include "../inc/ush.h"

int mx_get_twidth() {
    char *termtype = getenv("TERM");
    char *buff = malloc(2048);
    int success = 0;
    int col = 0;
    bool if_term = 0;

    if (termtype == 0) {
        termtype = mx_strdup("xterm-256color");
        if_term = 1;
    }
    if ((success = tgetent(buff, termtype)) < 0) {
        fprintf(stderr, "%s", MX_ETGTN);
        exit(1);
    }
    free(buff);
    if (if_term)
        mx_strdel(&termtype);
    col = tgetnum("co");
    return col;
}
