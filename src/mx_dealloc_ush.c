#include "../inc/ush.h"
// CHECK COMMENTS
void mx_dealloc_ush(t_ush **ush) {
//     mx_dealloc_blocks(&((*ush)->blocks));
    while ((*ush)->termconf->h_node)
        mx_pop_h_node_front(&((*ush)->termconf->h_node));
    mx_dealloc_termconf(&((*ush)->termconf));
    while ((*ush)->variable_list)
        mx_pop_front_variable(&((*ush)->variable_list));
    while ((*ush)->pwdilda_list)
        mx_pop_front_pwdilda(&((*ush)->pwdilda_list));
    while ((*ush)->jobs_list)
        mx_pop_jobs_node(&((*ush)->jobs_list), 1);
    free(*ush);
    (*ush) = NULL;
}
