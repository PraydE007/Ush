#include "ush.h"

static void burnish_cycle(t_b_node **blocks, t_b_node *p_b, t_b_node *p) {
    t_t_node *p_tt = NULL;
    char *buf = NULL;

    p_b = mx_push_block_back(blocks, NULL);
    p_tt = p->t_node;
    while (p_tt) {
        if (p_tt->type == -1 && buf != NULL) {
            mx_push_t_node_back(&(p_b->t_node), buf, 0);
            buf = NULL;
        }
        else if (p_tt->type == 0) {
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
    t_b_node *p = ush->blocks;
    t_b_node *blocks = NULL;
    t_b_node *p_b = NULL;

    while (p) {
        burnish_cycle(&blocks, p_b, p);
        p = p->next;
    }
    mx_dealloc_blocks(&(ush->blocks));
    ush->blocks = blocks;
}
