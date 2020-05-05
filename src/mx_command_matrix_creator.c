#include "../inc/ush.h"

char **mx_command_matrix_creator(t_t_node **comn) {
    t_t_node *pc = *comn;
    int size = mx_tlist_len(comn);
    int i = 0;
    char **com_mat = NULL;

    com_mat = (char **)malloc(sizeof(char *) * (size + 1));
    com_mat[size] = NULL;
    while (pc) {
        com_mat[i] = mx_strdup(pc->text);
        i++;
       
        pc = pc->next;
    }
    return com_mat;
}
