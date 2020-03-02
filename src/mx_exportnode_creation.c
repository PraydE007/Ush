#include "../inc/ush.h"

t_export  *mx_exportnode_creation(void) {
    t_export *node = (t_export*)malloc(sizeof(t_export));

    if (node) {
        node->key = NULL;
        node->value = NULL;
        node->next = NULL;
    }
    return node;	
}
