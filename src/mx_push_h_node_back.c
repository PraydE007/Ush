#include "../inc/ush.h"

void mx_push_h_node_back(t_h_node **h_node, char *buf) {
    t_h_node *new_node = mx_create_history_node(buf);
    t_h_node *p = (*h_node);

    if (p == NULL)
        (*h_node) = new_node;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
}
