#include "../inc/ush.h"

static void serial_number_setting(t_jobs **list, t_jobs **pl) {
    t_jobs *pl2 = *list;

    while (pl2) {
        if (pl2->serial_number > (*pl)->serial_number)
                pl2->serial_number = pl2->serial_number - 1;
        pl2 = pl2->next;
    }
}

static void pop_front_jobs(t_jobs **head) {
    t_jobs *pl = NULL;
    t_pid *pl_pid = NULL;

    mx_del_strarr(&(*head)->name);
    pl_pid = (*head)->pid_list;
    while (pl_pid)
        mx_pop_front_pid(&pl_pid);
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

static void pop_back_condition(t_jobs **pl) {
    t_jobs *buf = NULL;

    if ((*pl)->next->next) {
        buf = (*pl)->next->next;
        free((*pl)->next);
        (*pl)->next = buf;
    }
    else {
        free((*pl)->next);
        (*pl)->next = NULL;
    }
}
static void pop_anyplace_jobs(t_jobs **list, int index) {
    t_jobs *pl = *list;
    t_pid *pl_pid = NULL;

    while (pl->next->next) {
        if (pl->next->number == index)
            break;
        pl = pl->next;
    }
    mx_del_strarr(&pl->next->name);
    pl_pid = pl->next->pid_list;
    while (pl_pid)
        mx_pop_front_pid(&pl_pid);
    pop_back_condition(&pl);
}

void mx_pop_jobs_node(t_jobs **list, int index) {
    t_jobs *pl = *list;
    int lenth = 0;
    int node_check = 0;

    if ((*list != NULL) && (list != NULL)) {
        while (pl) {
            node_check++;
            if (pl->number == index)
                break;
            pl = pl->next;
        }
        lenth = mx_jobs_list_len(list);
        mx_jobs_sign_change(list, index);
        serial_number_setting(list, &pl);
        if (index == 1 || lenth == 1 || node_check == 1)
            pop_front_jobs(list);
        else
            pop_anyplace_jobs(list, index);
    }
}
