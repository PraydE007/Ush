#include "../inc/ush.h"

void mx_pop_front_pwdilda(t_pwdilda **head) {
    t_pwdilda  *pl = NULL;

    if ((*head != NULL) && (head != NULL)) {
        pl = (*head)->next;
        mx_strdel(&(*head)->key);
        mx_strdel(&(*head)->value);
        free(*head);
        *head = pl;
    }
}
