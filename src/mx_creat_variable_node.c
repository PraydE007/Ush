#include "../inc/ush.h"

t_variable *mx_creat_variable_node(void) {
    t_variable *node = (t_variable*)malloc(sizeof(t_variable));

    if (node) {
        node->key = NULL;
        node->value = NULL;
        node->next = NULL;
    }
    return node;
}
