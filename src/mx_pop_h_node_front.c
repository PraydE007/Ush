#include "../inc/ush.h"

void mx_pop_h_node_front(t_h_node **h_node) {
    t_h_node *p = (*h_node);

    if (*h_node && h_node) {
        while (p->back != NULL)
            p = p->back;
        if (p->next) {
            p = p->next;
            mx_strdel(&(p->back->buf));
            free(p->back);
            p->back = NULL;
            (*h_node) = p;
        }
        else {
            mx_strdel(&((*h_node)->buf));
            free(*h_node);
            (*h_node) = NULL;
        }
    }
}
