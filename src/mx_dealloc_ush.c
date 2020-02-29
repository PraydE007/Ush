#include "ush.h"

void mx_dealloc_ush(t_ush **ush) {
    mx_strdel(&((*ush)->buf));
    mx_dealloc_termconf(&((*ush)->termconf));
    // mx_dealloc_blocks(&((*ush)->blocks));
    free(*ush);
    (*ush) = NULL;
}
