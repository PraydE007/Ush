#include "../inc/ush.h"

t_h_node *mx_create_history_node(char *buf) {
    t_h_node *node = (t_h_node *)malloc(sizeof(t_h_node));

    node->buf = buf;
    node->next = NULL;
    return node;
}
