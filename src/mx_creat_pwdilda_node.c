#include "../inc/ush.h"

t_pwdilda *mx_creat_pwdilda_node(void) {
    t_pwdilda *node = (t_pwdilda*)malloc(sizeof(t_pwdilda));

    if (node) {
        node->key = NULL;
        node->value = NULL;
        node->next = NULL;
    }
    return node;	
}
