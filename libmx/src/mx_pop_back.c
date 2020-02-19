#include "libmx.h"

void mx_pop_back(t_list **list) {
    
    if(list != NULL) {
        t_list *pl = *list;
        while (pl->next->next != NULL) {
            pl = pl->next;
        }
        free(pl->next->data);
        free(pl->next);
        pl->next = NULL;
    }
}
