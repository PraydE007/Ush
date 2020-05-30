#include "../inc/ush.h"

t_h_node *mx_get_last_h_node(t_h_node **h_node) {
    t_h_node *p = (*h_node);

    while (p->next)
        p = p->next;
    return p;
}
