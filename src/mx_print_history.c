#include "../inc/ush.h"

void mx_print_history(t_termconf *cfg) {
    t_h_node *p = cfg->h_node;
    int i = 0;

    while (p) {
        i++;
        if (i >= cfg->h_len - 15)
        fprintf(stdout, "%5i  %s\n", i, p->buf);
        p = p->next;
    }
}
