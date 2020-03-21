#include "../inc/ush.h"

void mx_rd_print_pbc(t_termconf **cfg, char *buf) {
    char *num = NULL;

    if (!((*cfg)->isInThread)) {
        fprintf(stdout, "\r\x1B[0J%su$h> %s%s", (*cfg)->color, MX_ZER, buf);
        fprintf(stdout, "\r\x1B[%iC", (*cfg)->c_pos);
    }
    else {
        num = mx_itoa((*cfg)->c_pos);
        write((*cfg)->tty_fd, "\ru$h> ", 6);
        write((*cfg)->tty_fd, "\x1B[0J", mx_strlen("\x1B[0J"));
        write((*cfg)->tty_fd, buf, mx_strlen(buf));
        write((*cfg)->tty_fd, "\r\x1B[", mx_strlen("\r\x1B["));
        write((*cfg)->tty_fd, num, mx_strlen(num));
        write((*cfg)->tty_fd, "C", 1);
    }
    mx_strdel(&num);
    fflush(stdout);
}
