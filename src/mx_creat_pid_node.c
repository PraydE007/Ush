#include "../inc/ush.h"

t_pid *mx_creat_pid_node(int pid) {
    t_pid *node = (t_pid*)malloc(sizeof(t_pid));

    if (node) {
        node->pid = pid;
        node->next = NULL;
    }
    return node;
}
