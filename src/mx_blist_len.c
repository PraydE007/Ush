#include "../inc/ush.h"

int mx_blist_len(t_b_node **head) {
    t_b_node *p = (*head);
    int len = 0;

    while (p != NULL) {
        len += 1;
        p = p->next;
    }
    return len;
}
