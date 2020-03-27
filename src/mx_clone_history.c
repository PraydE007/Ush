#include "../inc/ush.h"

t_h_node *mx_clone_history(t_h_node **h_node) {
    t_h_node *new_node = NULL;
    t_h_node *p = (*h_node);

    if (*h_node && h_node) {
        while (p->back != NULL)
            p = p->back;
        while (p) {
            // new_buf = mx_buf_safe_realloc(p->buf, &(p->buf_size));
            mx_push_h_node_back(&new_node, mx_strdup_x(p->buf), p->buf_size);
            p = p->next;
        }
    }
    return new_node;
}
