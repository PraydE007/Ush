#include "../inc/ush.h"

void mx_replace_subst(t_ush *ush, t_b_node **node) {
    t_t_node *p = (*node)->t_node;
    char *var_name = NULL;

    while (p) {
        if (p->type == 3) {
            var_name = mx_strdup_x(p->text);
            mx_strdel(&(p->text));
            p->text = mx_substitution_making(ush, var_name);
            mx_strdel(&(var_name));
            if (p->text)
                mx_text_node_split(&p);
            else
                p->text = mx_strnew_x(1);
        }
        p = p->next;
    }
}
