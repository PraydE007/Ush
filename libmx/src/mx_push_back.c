#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *node = mx_create_node(data);
    t_list *pl = *list;

    if (pl == NULL) {
        *list = node;
        return;
    }

    while (pl->next != NULL) {
        pl = pl->next;
    }
    pl->next = node;    
}
