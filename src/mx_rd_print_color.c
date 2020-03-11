#include "../inc/ush.h"

void mx_rd_print_color(t_termconf **cfg) {
    if (!((*cfg)->isInThread))
        fprintf(stdout, "%su$h> ", (*cfg)->color);
    else
        write((*cfg)->tty_fd, "u$h> ", 5);
    fflush(stdout);
}
