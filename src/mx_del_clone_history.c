#include "../inc/ush.h"

void mx_del_clone_history(t_termconf **cfg) {
    while ((*cfg)->clone)
        mx_pop_h_node_front(&((*cfg)->clone));
    (*cfg)->clone = NULL;
}
