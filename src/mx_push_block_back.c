#include "ush.h"

void mx_push_block_back(t_b_node **head, char **block) {
    t_b_node *new_node = mx_create_block_node(block);
    t_b_node *p = (*head);

    if (p == NULL)
        (*head) = new_node;
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
}
