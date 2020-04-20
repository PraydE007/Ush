#include "../inc/ush.h"

void mx_push_back_pwdilda(t_pwdilda **list, char *kay, char *value) {
    t_pwdilda *node = mx_creat_pwdilda_node();
    t_pwdilda *pl = *list;

    node->key = mx_strdup(kay);
    node->value = mx_strdup(value);
    if (pl == NULL) {
        *list = node;
        return;
    }
    while (pl->next != NULL) {
        pl = pl->next;
    }
    pl->next = node;
}
