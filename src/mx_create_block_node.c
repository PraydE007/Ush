#include "ush.h"

t_b_node *mx_create_block_node(char **block) {
    t_b_node *node = (t_b_node *)malloc(sizeof(t_b_node));

    node->block = block;
    node->next = NULL;
    return node;
}
