#include "../inc/ush.h"

static t_b_node *burnish_cycle(t_b_node **block, t_t_node *p_tt) {
    t_b_node *new = mx_create_block_node(NULL);
    char *buf = NULL;

    p_tt = (*block)->t_node;
    while (p_tt) {
        if (p_tt->type == -1 && buf != NULL) {
            mx_push_t_node_back(&(new->t_node), buf, 0);
            buf = NULL;
        }
        else if (p_tt->type == 0 || p_tt->type == 1
            || p_tt->type == 2 || p_tt->type == 3)
            buf = mx_strjoin_free(buf, p_tt->text);
        p_tt = p_tt->next;
    }
    if (buf) {
        mx_push_t_node_back(&(new->t_node), buf, 0);
        buf = NULL;
    }
    mx_dealloc_blocks(block);
    return new;
}

void mx_parse_burnish_pro(t_ush *ush, t_b_node **block) {
    mx_replace_tild(&(ush->pwdilda_list), block);
    mx_replace_variables(ush, block);
    mx_replace_subst(ush, block);
    (*block) = burnish_cycle(block, NULL);
    if ((*block)->t_node)
        mx_check_commands(ush, *block);
}
