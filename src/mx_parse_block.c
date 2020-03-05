#include "ush.h"

t_b_node *mx_parse_block(t_t_node **head) {
    t_t_node *p = (*head);
    t_b_node *blocks = NULL;
    t_b_node *p_b = NULL;
    char *buf = NULL;
    int err_ch = 0;
    int type = 0;

    while (p) {
        p_b = mx_push_block_back(&blocks, NULL);
        for (int i = 0; p->text[i] != '\0'; i++) {
            err_ch = i;
            // ADD OTHER CASES
            if (p->text[i] == ' ') {
                type = -1;
                buf = mx_space_parse(&(p->text[i]), &i);
            }
            else if (p->text[i] == '\\') {
                type = 0;
                buf = mx_slash_parse(&(p->text[i]), &i);
            }
            else if (p->text[i] == '\'') {
                type = 0;
                buf = mx_sinmrk_parse(&(p->text[i + 1]), &i);
            }
            else if (p->text[i] == '\"') {
                type = 0;
                buf = mx_doumrk_parse(&(p->text[i + 1]), &i);
            }
            else {
                type = 0;
                buf = mx_text_parse(&(p->text[i]), &i);
            }

            if (buf)
                mx_push_t_node_back(&(p_b->t_node), buf, type);
            else {
                fprintf(stderr, MX_PIZDA, p->text[err_ch]);
                mx_dealloc_blocks(&blocks);
                return NULL;
            }
        }
        p = p->next;
    }
    return blocks;
}
