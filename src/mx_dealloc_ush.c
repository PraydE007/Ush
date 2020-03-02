#include "../inc/ush.h"

void mx_dealloc_ush(t_ush **ush) {
    mx_strdel(&((*ush)->buf));
    mx_dealloc_termconf(&((*ush)->termconf));
    // mx_dealloc_blocks(&((*ush)->blocks));
    while ((*ush)->export_list)
        mx_pop_front_export(&((*ush)->export_list));
    while ((*ush)->export_list)
        mx_pop_front_variable(&((*ush)->variable_list));
    free(*ush);
    (*ush) = NULL;
}
