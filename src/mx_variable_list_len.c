#include "../inc/ush.h"

int mx_variable_list_len(t_variable **head) {
    t_variable *p = (*head);
    int len = 0;

    while (p != NULL) {
        len += 1;
        p = p->next;
    }
    return len;
}