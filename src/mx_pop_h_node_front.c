#include "../inc/ush.h"

void mx_pop_h_node_front(t_h_node **h_node) {
    t_h_node *p = NULL;

    if ((*h_node != NULL) && (h_node != NULL)) {
        p = (*h_node)->next;
        if ((*h_node)->buf)
            mx_strdel(&((*h_node)->buf));
        free(*h_node);
        (*h_node) = p;
    }
}
