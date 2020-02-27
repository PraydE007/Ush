#include "ush.h"

void mx_pop_block_front(t_b_node **head) {
    t_b_node *p = NULL;

    if ((*head != NULL) && (head != NULL)) {
        p = (*head)->next;
        free(*head);
        (*head) = p;
    }
}
