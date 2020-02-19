#include "libmx.h"

void mx_pop_front(t_list **head)  {
    
    if (*head != NULL) {
        t_list *pl = (*head)->next;
        free(*head);
        *head = pl;
    }
}
