#include "../inc/ush.h"
//check if we need this faction
void mx_pop_front_export(t_export **head) {
    t_export  *pl = NULL;

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
