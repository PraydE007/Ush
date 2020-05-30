#include "../inc/ush.h"

t_h_node *mx_get_h_node_index(t_h_node **h_node, int id) {
    t_h_node *p = (*h_node);
    int i = 0;

    if (id < 0)
        return p;
    while (p->next) {
        if (i == id)
            break;
        i++;
        p = p->next;
    }
    return p;
}
