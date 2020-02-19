#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    t_list *pli = lst;
    t_list *plj = lst;
    t_list *buf;

    while (pli->next != NULL) {
        while (plj->next != NULL) {
            if (cmp(plj->data, plj->next->data)) {
                buf = mx_create_node(plj->data);
                plj->data = plj->next->data;
                plj->next->data = buf->data;
                free(buf);
            }
            plj = plj->next;
        }
        plj = lst;
        pli = pli->next;
    }
    return lst;
}
