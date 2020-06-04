#include "../inc/ush.h"

void mx_read_termconf(t_termconf *termconf) {
    tcgetattr(0, &(termconf->tty));
    termconf->savetty = termconf->tty;
    termconf->tty.c_lflag &= ~(ICANON|ECHO|ISIG);
    termconf->tty.c_cc[VMIN] = 1;
}
