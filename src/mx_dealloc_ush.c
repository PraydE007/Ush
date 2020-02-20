#include "ush.h"

void mx_dealloc_ush(t_ush **ush) {
    mx_strdel(&((*ush)->buf));
    mx_dealloc_termconf(&((*ush)->termconf));
    free(*ush);
    (*ush) = NULL;
}
