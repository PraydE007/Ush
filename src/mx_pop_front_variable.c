#include "../inc/ush.h"

void mx_pop_front_variable(t_variable **head) {
    t_variable  *pl = NULL;

    if ((*head != NULL) && (head != NULL)) {
        if ((*head)->next) {
            pl = (*head)->next;
            mx_strdel(&(*head)->key);
            mx_strdel(&(*head)->value);
            free(*head);
            *head = pl;
        }
        else {
            mx_strdel(&((*head)->key));
            mx_strdel(&((*head)->value));
            free(*head);
            (*head) = NULL;
        }
    }
}
