#include "../inc/ush.h"

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
        else if (p_tt->type == 0 || p_tt->type == 1 || p_tt->type == 2) {
            buf = mx_strjoin_free(buf, p_tt->text);
        }
        p_tt = p_tt->next;
    }
    if (buf) {
        mx_push_t_node_back(&(p_b->t_node), buf, 0);
        buf = NULL;
    }
}

void mx_parse_burnish(t_ush *ush) {
    t_b_node *blocks = NULL;
    t_b_node *clone = NULL;
    t_b_node *p = NULL;

    mx_outlst(ush); //
    clone = mx_clone_blocks(&(ush->blocks));
    mx_dealloc_blocks(&(ush->blocks));
    p = clone;
    while (p) {
        mx_replace_tild(&p);
        mx_replace_variables(ush, &p);
        burnish_cycle(&(ush->blocks), &p);
        mx_check_commands(ush);
        mx_dealloc_blocks(&(ush->blocks));
        p = p->next;
    }
    mx_dealloc_blocks(&clone);
}
