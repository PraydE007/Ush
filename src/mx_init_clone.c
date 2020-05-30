#include "../inc/ush.h"

void mx_init_clone(t_termconf **cfg) {
    (*cfg)->clone = mx_clone_history(&((*cfg)->h_node));
    mx_push_h_node_back(&((*cfg)->clone), mx_strnew_x(1));
    (*cfg)->chsn = mx_get_last_h_node(&((*cfg)->clone));
    (*cfg)->h_len += 1;
    (*cfg)->c_pos += 0;
    (*cfg)->h_pos = (*cfg)->h_len - 1;
}
