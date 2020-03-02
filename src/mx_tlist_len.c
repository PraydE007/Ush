#include "ush.h"

//clean "if (strcmp(p->text, " ") != 0)"" when parsing is ready
int mx_tlist_len(t_t_node **head) {
    t_t_node *p = (*head);
    int len = 0;

    while (p != NULL) {
        if (strcmp(p->text, " ") != 0)
            len += 1;
        p = p->next;
    }
    return len;
}
