#include "../inc/ush.h"

void mx_replace_variables(t_ush *ush, t_b_node **node) {
    t_t_node *p = (*node)->t_node;
    char *var_name = NULL;

    while (p) {
        if (p->type == 1) {
            var_name = mx_strdup(p->text);
            mx_strdel(&(p->text));
            p->text = mx_get_variable(ush, var_name);
            mx_strdel(&(var_name));
        }
        p = p->next;
    }
}
