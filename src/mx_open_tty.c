#include "../inc/ush.h"

void mx_open_tty(t_termconf **cfg) {
    (*cfg)->tty_fd = open("/dev/tty", O_WRONLY);
}
