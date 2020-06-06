#include "../inc/ush.h"

void mx_replace_subst(t_ush *ush, t_b_node **node) {
    t_t_node *p = (*node)->t_node;
    char *var_name = NULL;

    while (p) {
        if (p->type == 3) {
            // system("leaks -q ush");
            var_name = mx_strdup_x(p->text);
            // system("leaks -q ush");
            mx_strdel(&(p->text));
            // system("leaks -q ush");
            p->text = mx_substitution_making(ush, var_name);
            // system("leaks -q ush");
            mx_strdel(&(var_name));
            // system("leaks -q ush");
            if (!(p->text)) {
                p->text = mx_strnew_x(1);
            }
            // if (p->text) {
            //     mx_text_node_split(&p);
            //     mx_printstr("1\n");
            // }
            // else {
            //     p->text = mx_strnew_x(1);
            //     mx_printstr("2\n");
            // }
            // system("leaks -q ush");
        }
        p = p->next;
    }
}
