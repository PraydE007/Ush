#include "../inc/ush.h"

void mx_outlst(t_ush *ush) {
    t_b_node *block = ush->blocks;
    t_t_node *x = NULL;

    while (block) {
        x = block->t_node;
        while (x != NULL) {
            fprintf(stdout, "\x1b[32m [\x1b[0m %s \x1b[32m]\x1b[0m ", x->text);
            fflush(stdout);
            x = x->next;
        }
        mx_printstr("\n");
        x = block->t_node;
        while (x != NULL) {
            fprintf(stdout, "\x1b[32m [\x1b[0m %i \x1b[32m]\x1b[0m ", x->type);
            fflush(stdout);
            x = x->next;
        }
        mx_printstr("\n");
        block = block->next;
    }
    fprintf(stdout, "\n");
}
