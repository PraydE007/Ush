#include "../inc/ush.h"

void mx_replace_tild(t_pwdilda **list, t_b_node **node) {
    t_t_node *p = (*node)->t_node;
    char *var_name = NULL;

    while (p) {
        if (p->type == 2) {
            var_name = mx_strdup_x(p->text);
            mx_strdel(&(p->text));
            p->text = mx_tildastr(list, var_name);
            mx_strdel(&(var_name));
        }
        p = p->next;
    }
}
