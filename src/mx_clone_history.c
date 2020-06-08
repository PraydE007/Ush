#include "../inc/ush.h"
// CHECK COMMENTS
void printStrInt(char *str) {
    int i = 0;

    while (str[i] != '\0') {
        mx_printint(str[i]);
        mx_printstr(" ");
        i++;
    }
    mx_printstr("\n");
}

t_h_node *mx_clone_history(t_h_node **h_node) {
    t_h_node *new_node = NULL;
    t_h_node *p = (*h_node);
    // char *cl_str = NULL;

    if (*h_node && h_node) {
        while (p) {
            mx_push_h_node_back(&new_node, mx_strdup_x(p->buf));
            p = p->next;
        }
    }
    return new_node;
}
