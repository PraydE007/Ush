#include "../inc/ush.h"

void mx_rd_print_old(t_termconf **cfg) {
    t_h_node *c = (*cfg)->clone;

    if (!((*cfg)->isInThread)) {
        fprintf(stdout, "\r\x1B[0J\x1B[38;05;243mu$h> %s%s\n", c->buf, MX_ZER);
    }
    else {
        write((*cfg)->tty_fd, "\r\x1B[0Ju$h> ", mx_strlen("\r\x1B[0Ju$h> "));
        write((*cfg)->tty_fd, c->buf, mx_strlen(c->buf));
        write((*cfg)->tty_fd, "\n", 1);
    }
    fflush(stdout);
}
