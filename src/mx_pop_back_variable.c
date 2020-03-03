#include "../inc/ush.h"

void mx_pop_back_variable(t_variable **head)  {
    t_variable *pl = NULL;

    if ((*head == NULL) && (head == NULL))
        return;
    if ((*head)->next == NULL) {
        mx_strdel(&((*head)->key));
        mx_strdel(&((*head)->value));
        free(*head);
        (*head) = NULL;
    }
    else {
        pl = *head;
        while (pl->next->next != NULL)
            pl = pl->next;
        mx_strdel(&(pl->next->key));
        mx_strdel(&(pl->next->value));
        free(pl->next);
        pl->next = NULL;
    }
}
