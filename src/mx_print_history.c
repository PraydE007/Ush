#include "../inc/ush.h"

void mx_print_history(t_termconf *cfg) {
    t_h_node *p = cfg->h_node;
    int i = 0;

    while (p->back)
        p = p->back;
    while (p) {
        i++;
        fprintf(stdout, "%5i  %s\n", i, p->buf);
        p = p->next;
    }
}
