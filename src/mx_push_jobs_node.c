#include "../inc/ush.h"

static char **strarrdup(char **strarr) {
    char **copy = NULL;
    int size = mx_strarrlen(strarr);

    copy = (char **)malloc(sizeof(char *) * (size + 1));
    copy[size] = NULL;
    for (int i = 0; strarr[i]; i++)
        copy[i] = mx_strdup(strarr[i]);
    if (copy == NULL)
        return NULL;
    return copy;
}

static void push_front_jobs(t_jobs **list, t_jobs *node, int lenth) {
    node->serial_number = lenth + 1;
    node->next = *list;
    *list = node;
}

static void push_sign_change(t_jobs **list) {
    t_jobs *pl = *list;

    while (pl != NULL) {
        if (pl->sign == '-')
            pl->sign = ' ';
        else if (pl->sign == '+')
            pl->sign = '-';
        pl = pl->next;
    }
}

static void push_anyplace_jobs(t_jobs **list, t_jobs *node, int lenth) {
    t_jobs *pl = *list;
    int i = 1;

    node->serial_number = lenth + 1;
    while (i < lenth) {
        if (pl->number != (pl->next->number - 1)) {
            node->number = pl->number + 1;
            node->next = pl->next;
            pl->next = node;
            return;
        }
        i++;
        pl = pl->next;
    }
    node->number = lenth + 1;
    pl->next = node;
}

void mx_push_jobs_node(t_jobs **list, t_pid **pids, char **command,
                                                    char ***pipe_command) {
    t_jobs *node = mx_creat_jobs_node();
    int lenth = mx_jobs_list_len(list);

    if (command)
        node->name = strarrdup(command);
    else if (pipe_command)
        node->name = mx_strararrdup(pipe_command);
    node->pid_list = *pids;
    if (*list == NULL) {
        *list = node;
        return;
    }
    push_sign_change(list);
    if ((*list)->number != 1) {
        push_front_jobs(list, node, lenth);
        return;
    }
    else
        push_anyplace_jobs(list, node, lenth);

    // while (i < lenth) {
    //     if (pl->number != (pl->next->number - 1)) {
    //         node->number = pl->number + 1;
    //         node->next = pl->next;
    //         pl = node;
    //         return;
    //     }
    //     i++;
    //     pl = pl->next;
    // }
    // node->number = lenth + 1;
    // pl->next = node;
}
