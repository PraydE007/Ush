#include "../inc/ush.h"
//CHECK IF WE NEED THIS FUNCTION
void mx_push_back_export(t_export **list, char **kv) {
    t_export *node = mx_exportnode_creation();
    t_export *pl = *list;

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
