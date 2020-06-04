#include "../inc/ush.h"

void mx_pop_front_pid(t_pid **head) {
    t_pid  *pl = NULL;

    if ((*head != NULL) && (head != NULL)) {
        if ((*head)->next) {
            pl = (*head)->next;
            free(*head);
            *head = pl;
        }
        else {
            free(*head);
            (*head) = NULL;
        }   
    }
}
