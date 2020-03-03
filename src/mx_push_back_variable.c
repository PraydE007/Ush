#include "../inc/ush.h"

void mx_push_back_variable(t_variable **list, char **kv) {
    t_variable *node = mx_variablenode_creation();
    t_variable *pl = *list;

    node->key = mx_strdup(kv[0]);
    if (kv[1])
        node->value = mx_strdup(kv[1]);
    if (pl == NULL) {
        *list = node;
        return;
    }
    while (pl->next != NULL) {
        pl = pl->next;
    }
    pl->next = node;
}
