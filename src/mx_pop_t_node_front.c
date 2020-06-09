#include "../inc/ush.h"

void mx_pop_t_node_front(t_t_node **head) {
    t_t_node *p = NULL;

    if ((*head != NULL) && (head != NULL)) {
        p = (*head)->next;
        mx_strdel(&((*head)->text));
        free(*head);
        (*head) = p;
    }
}
