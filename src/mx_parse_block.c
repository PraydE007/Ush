#include "../inc/ush.h"

static void check_for_parse(t_t_node *p, char **buf, int *i, int *type) {
    if (p->text[(*i)] == ' ')
        (*buf) = mx_space_parse(&(p->text[(*i)]), i);
    else {
        (*type) = 0;
        if (p->text[(*i)] == '\\')
            (*buf) = mx_slash_parse(&(p->text[(*i)]), i);
        else if (p->text[(*i)] == '\'')
            (*buf) = mx_sinmrk_parse(&(p->text[(*i) + 1]), i);
        else if (p->text[(*i)] == '\"')
            (*buf) = mx_doumrk_parse(NULL, &(p->text[(*i) + 1]), i);
        else if (p->text[(*i)] == '$')
            (*buf) = mx_dollar_parse(&(p->text[(*i) + 1]), i, type);
        else if (p->text[(*i)] == '`')
            (*buf) = mx_subst_parse(&(p->text[(*i) + 1]), i, type);
        else if (p->text[(*i)] == '~')
            (*buf) = mx_tild_parse(&(p->text[(*i) + 1]), i, type);
        else
            (*buf) = mx_text_parse(&(p->text[(*i)]), i);
    }
}

static int check_error(t_b_node *blocks, t_b_node *p_b, char *buf, int type) {
    if (buf)
        mx_push_t_node_back(&(p_b->t_node), buf, type);
    else {
        mx_dealloc_blocks(&blocks);
        return 0;
    }
    return 1;
}

t_b_node *mx_parse_block(t_t_node **head, int err_ch, int type) {
    t_t_node *p = (*head);
    t_b_node *blocks = NULL;
    t_b_node *p_b = NULL;
    char *buf = NULL;

    while (p) {
        p_b = mx_push_block_back(&blocks, NULL);
        for (int i = 0; p->text[i] != '\0'; i++) {
            err_ch = i;
            type = -1;
            check_for_parse(p, &buf, &i, &type);
            if (!check_error(blocks, p_b, buf, type)) {
                fprintf(stderr, MX_PIZDA, p->text[err_ch]);
                return NULL;
            }
        }
        p = p->next;
    }
    return blocks;
}
