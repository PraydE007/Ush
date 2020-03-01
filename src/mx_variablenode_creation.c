#include "ush.h"

t_variable *mx_variablenode_creation(void) {
    t_variable *node = (t_variable*)malloc(sizeof(t_variable));

    if (node) {
        node->key = NULL;
        node->value = NULL;
        node->next = NULL;
    }
    return node;	
}
