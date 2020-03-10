#include "../inc/ush.h"

void mx_dealloc_termconf(t_termconf **termconf) {
    mx_strdel(&((*termconf)->buf));
    mx_strdel(&((*termconf)->color));
    free(*termconf);
    (*termconf) = NULL;
}
