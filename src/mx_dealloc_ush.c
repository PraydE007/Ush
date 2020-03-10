#include "../inc/ush.h"

void mx_dealloc_ush(t_ush **ush) {
    // mx_dealloc_blocks(&((*ush)->blocks));
    // while ((*ush)->export_list)
    //     mx_pop_front_export(&((*ush)->export_list));
    while ((*ush)->termconf->h_node)
        mx_pop_h_node_front(&((*ush)->termconf->h_node));
    mx_dealloc_termconf(&((*ush)->termconf));
    while ((*ush)->variable_list)
        mx_pop_front_variable(&((*ush)->variable_list));
    free(*ush);
    (*ush) = NULL;
}
