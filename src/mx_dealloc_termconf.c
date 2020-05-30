#include "../inc/ush.h"

void mx_dealloc_termconf(t_termconf **termconf) {
    if ((*termconf)->isInThread)
        close((*termconf)->tty_fd);
    (*termconf)->chsn = NULL;
    mx_strdel(&((*termconf)->color));
    free(*termconf);
    (*termconf) = NULL;
}
