#include "../inc/ush.h"

int mx_tlist_len(t_t_node **list) {
    t_t_node *p = (*list);
    int len = 0;

    while (p != NULL) {
        len += 1;
        p = p->next;
    }
    return len;
}
