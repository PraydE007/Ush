#include "../inc/ush.h"

t_h_node *mx_create_history_node(t_h_node *back, char *buf, int buf_size) {
    t_h_node *node = (t_h_node *)malloc(sizeof(t_h_node));

    node->back = back;
    node->buf = buf;
    node->buf_size = buf_size;
    node->next = NULL;
    return node;
}
