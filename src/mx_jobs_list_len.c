#include "../inc/ush.h"

int mx_jobs_list_len(t_jobs **list) {
    t_jobs *pl = (*list);
    int len = 0;

    while (pl != NULL) {
        len += 1;
        pl = pl->next;
    }
    return len;
}
