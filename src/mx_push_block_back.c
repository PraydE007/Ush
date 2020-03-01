#include "ush.h"

t_b_node *mx_push_block_back(t_b_node **head, t_t_node *t_node) {
    t_b_node *new_node = mx_create_block_node(t_node);
    t_b_node *p = (*head);

    if (p == NULL)
        (*head) = new_node;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
    return new_node;
}
