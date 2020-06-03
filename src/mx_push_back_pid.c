#include "../inc/ush.h"

void mx_push_back_pid(t_pid **list, int pid) {
    t_pid *node = mx_creat_pid_node(pid);
    t_pid *pl = *list;

    if (pl == NULL) {
        *list = node;
        return;
    }
    while (pl->next != NULL) {
        pl = pl->next;
    }
    pl->next = node;
}
