#include "../inc/libmx.h"

void mx_pop_front(t_list **head)  {
    t_list  *pl = NULL;
    
    if ((*head != NULL) && (head != NULL)) {
        if ((*head)->next) {
            pl = (*head)->next;
            free(pl->data);
            free(*head);
            *head = pl;
        }
        else {
            free(pl->data);
            free(*head);
            (*head) = NULL;
        }
    }
}
