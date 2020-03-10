#include "../inc/ush.h"

void mx_push_h_node_back(t_h_node **h_node, char *buf, int buf_size) {
    t_h_node *new_node = NULL;
    t_h_node *p = (*h_node);

    if (p == NULL) {
        new_node = mx_create_history_node(NULL, buf, buf_size);
        (*h_node) = new_node;
    }
    else {
        while (p->next != NULL)
            p = p->next;
        new_node = mx_create_history_node(p, buf, buf_size);
        p->next = new_node;
        (*h_node) = new_node;
    }
}
