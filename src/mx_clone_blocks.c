#include "../inc/ush.h"

t_b_node *mx_clone_blocks(t_b_node **head) {
    t_b_node *clone = NULL;
    t_t_node *words = NULL;
    t_b_node *pb = *head;
    t_t_node *pt = NULL;

    while (pb) {
        pt = pb->t_node;
        while (pt) {
            mx_push_t_node_back(&words, mx_strdup_x(pt->text), pt->type);
            pt = pt->next;
        }
        mx_push_block_back(&clone, words);
        words = NULL;
        pb = pb->next;
    }
    return clone;
}
