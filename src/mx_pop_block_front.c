#include "ush.h"

void mx_pop_block_front(t_b_node **head) {
    t_b_node *p = NULL;

    if ((*head != NULL) && (head != NULL)) {
        p = (*head)->next;
        while ((*head)->t_node)
            mx_pop_t_node_front(&((*head)->t_node));
        free(*head);
        (*head) = p;
    }
}
