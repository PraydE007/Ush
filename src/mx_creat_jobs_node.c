#include "../inc/ush.h"

t_jobs *mx_creat_jobs_node(void) {
    t_jobs *node = (t_jobs*)malloc(sizeof(t_jobs));

    if (node) {
        node->number = 1;
        node->serial_number = 1;
        node->sign = '+';
        node->name = NULL;
        node->pid_list = NULL;
        node->next = NULL;
    }
    return node;
}
