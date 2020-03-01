#include "ush.h"

t_b_node *mx_create_block_node(t_t_node *t_node) {
    t_b_node *node = (t_b_node *)malloc(sizeof(t_b_node));

    node->t_node = t_node;
    node->next = NULL;
    return node;
}
