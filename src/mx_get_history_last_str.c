#include "../inc/ush.h"

char *mx_get_history_last_str(t_h_node **h_node) {
    t_h_node *p = (*h_node);

    while (p->next != NULL)
        p = p->next;
    return p->buf;
}
