#include "../inc/ush.h"
//CHECK COMMENTS
static void burnish_cycle(t_b_node **blocks, t_b_node **p) {
    t_b_node *p_b = NULL;
    t_t_node *p_tt = NULL;
    char *buf = NULL;

    p_b = mx_push_block_back(blocks, NULL);
    p_tt = (*p)->t_node;
    while (p_tt) {
        if (p_tt->type == -1 && buf != NULL) {
            mx_push_t_node_back(&(p_b->t_node), buf, 0);
            buf = NULL;
        }
        else if (p_tt->type == 0 || p_tt->type == 1
            || p_tt->type == 2 || p_tt->type == 3)
            buf = mx_strjoin_free(buf, p_tt->text);
        p_tt = p_tt->next;
    }
    if (buf) {
        mx_push_t_node_back(&(p_b->t_node), buf, 0);
        buf = NULL;
    }
}

void mx_parse_burnish(t_ush *ush) {
    t_b_node *clone = NULL;
    t_b_node *p = NULL;

    // mx_outlst(ush); //
    clone = mx_clone_blocks(&(ush->blocks));
    mx_dealloc_blocks(&(ush->blocks));
    p = clone;
    while (p) {
        // system("leaks -q ush");
        mx_replace_tild(&(ush->pwdilda_list), &p);
        // system("leaks -q ush");
        mx_replace_variables(ush, &p);
        // system("leaks -q ush");
        mx_replace_subst(ush, &p);
        // system("leaks -q ush");
        burnish_cycle(&(ush->blocks), &p);
        // system("leaks -q ush");
        if (ush->blocks->t_node)
            mx_check_commands(ush);
        // system("leaks -q ush");
        mx_dealloc_blocks(&(ush->blocks));
        // system("leaks -q ush");
        p = p->next;
    }
    mx_dealloc_blocks(&clone);
}
