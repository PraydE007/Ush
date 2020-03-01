#include "ush.h"

t_b_node *mx_parse_block(t_t_node **head) {
    t_t_node *p = (*head);
    t_b_node *blocks = NULL;
    t_b_node *p_b = NULL;
    char *buf = NULL;
    int err_ch = 0;

    while (p) {
        p_b = mx_push_block_back(&blocks, NULL);
        for (int i = 0; p->text[i] != '\0'; i++) {
            err_ch = i;
            // ADD OTHER CASES
            if (p->text[i] == ' ')
                buf = mx_space_parse(&(p->text[i]), &i);
            else if (p->text[i] == '\'')
                buf = mx_sinmrk_parse(&(p->text[i + 1]), &i);
            else if (p->text[i] == '\"')
                buf = mx_doumrk_parse(&(p->text[i + 1]), &i);
            else
                buf = mx_text_parse(&(p->text[i]), &i);

            if (buf)
                mx_push_t_node_back(&(p_b->t_node), buf);
            else {
                fprintf(stderr, MX_PIZDA, p->text[err_ch]);
                // fprintf(stdout, "CO: %i, CH: %c\n", err_ch, p->text[err_ch]);
                exit(666);
            }
            // fprintf(stdout, "CO: %i, CH: %c\n", err_ch, p->text[err_ch]);
        }
        p = p->next;
    }
    return blocks;
}
