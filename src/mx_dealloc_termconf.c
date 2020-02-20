#include "ush.h"

void mx_dealloc_termconf(t_termconf **termconf) {
    free(*termconf);
    (*termconf) = NULL;
}
