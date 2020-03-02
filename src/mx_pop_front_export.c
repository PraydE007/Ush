#include "../inc/ush.h"

void mx_pop_front_export(t_export **head) {
    t_export  *pl = NULL;

    if (*head != NULL) {
        pl = (*head)->next;
        mx_strdel(&(*head)->key);
        mx_strdel(&(*head)->value);
        free(*head);
        *head = pl;
    }
}
