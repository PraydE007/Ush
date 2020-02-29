#include "ush.h"

t_env  *mx_envnode_creation(void) {
    t_env *node = (t_env *)malloc(sizeof(t_env));

    if (node) {
        node->key = NULL;
        node->value = NULL;
        node->next = NULL;
    }
    return node;
}
