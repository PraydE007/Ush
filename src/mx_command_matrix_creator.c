#include "../inc/ush.h"

char **mx_command_matrix_creator(t_t_node **comn) {
    t_t_node *pc = *comn;
    int size = mx_tlist_len(comn);
    int i = 0;
    char **com_mat = NULL;

    com_mat = (char **)malloc(sizeof(char *) * (size + 1));
    com_mat[size] = NULL;
    while (pc) {
        // printf("pc->text[%d]: %s\n", i, pc->text);
        com_mat[i] = mx_strdup(pc->text);
        // printf(" com_mat[%d]: %s\n", i, com_mat[i]);
        i++;
       
        pc = pc->next;
    }
    return com_mat;
}
