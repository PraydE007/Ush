#include "../inc/ush.h"

static void check_for_parse(t_wa **wa, char *blk, int *i, int *type) {
    if (blk[(*i)] == ' ')
        (*wa)->buf = mx_space_parse(&blk[(*i)], i);
    else {
        (*type) = 0;
        if (blk[(*i)] == '\\')
            (*wa)->buf = mx_slash_parse(&blk[(*i)], i);
        else if (blk[(*i)] == '\'')
            (*wa)->buf = mx_sinmrk_parse(&blk[(*i) + 1], i);
        else if (blk[(*i)] == '\"')
            (*wa)->buf = mx_doumrk_parse((*wa)->ush, &blk[(*i) + 1], i);
        else if (blk[(*i)] == '$')
            (*wa)->buf = mx_dollar_parse(&blk[(*i) + 1], i, type);
        else if (blk[(*i)] == '`')
            (*wa)->buf = mx_subst_parse(&blk[(*i) + 1], i, type);
        else if (blk[(*i)] == '~')
            (*wa)->buf = mx_tild_parse(&blk[(*i) + 1], i, type);
        else
            (*wa)->buf = mx_text_parse(&blk[(*i)], i);
    }
}

static int check_error(t_b_node *block, char *buf, int type) {
    if (buf)
        mx_push_t_node_back(&(block->t_node), buf, type);
    else {
        mx_dealloc_blocks(&block);
        return 0;
    }
    return 1;
}

void mx_parse_block_pro(t_ush *ush, char *blk) {
    t_b_node *block = mx_create_block_node(NULL);
    t_wa *wa = mx_create_workaround(ush);
    int type = -1;

    for (int i = 0; blk[i] != '\0'; i++, type = -1) {
        check_for_parse(&wa, blk, &i, &type);
        if (!check_error(block, wa->buf, type)) {
            fprintf(stderr, MX_PIZDA, blk[i]);
            ush->exit_code = 127;
            free(wa);
            return;
        }
    }
    free(wa);
    mx_parse_burnish_pro(ush, &block);
    mx_dealloc_blocks(&block);
}
