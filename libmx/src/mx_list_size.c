#include "libmx.h"

int mx_list_size(t_list *list) {
    int count = 0;
    t_list *pl = list;
    
    while (pl != NULL) {
        pl = pl->next;
        count++;
    }
    return count;
}
