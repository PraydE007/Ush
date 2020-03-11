#include "../inc/ush.h"

void mx_print_history(t_ush *ush) {
    t_h_node *p = ush->termconf->h_node;
    int i = 1;

    while (p->back != NULL)
        p = p->back;
    while (p->next != NULL) {
        fprintf(stdout, "%5i  %s\n", i, p->buf);
        i++;
        p = p->next;
    }
    fprintf(stdout, "%5i  %s\n", i, "history");
}
