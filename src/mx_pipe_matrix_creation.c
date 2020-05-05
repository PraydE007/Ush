#include "../inc/ush.h"

static char *pipe_parsing(t_ush *ush, char *command) {
    int lenth = 0;
    int i = 0;
    char *pipemat = NULL;

    for (; command[i]; i++, ush->triger++) {
        if (command[i] == '|')
            break;
        lenth++;
    }
    if (lenth > 0) 
        pipemat = mx_strndup(command, lenth);
    if (command[i + 1]) 
        ush->triger++;
    else {
        ush->triger = 0;
        if (ush->k < ush->size - 1)
            ush->k++;
    }
    return pipemat;
}

static void filling_cycle(t_ush *ush, char ***pipemat, char **command,
                                                            int commat_size) {
    char *copy = NULL;
    
    for (int j = 0; j < commat_size; j++) {
        if (!mx_is_pipe(NULL, &command[ush->k][ush->triger])) {
            pipemat[ush->i][j] = strdup(&command[ush->k][ush->triger]);
            if (ush->k < ush->size - 1)
                ush->k++;
            ush->triger = 0;
        }
        else {
            copy = pipe_parsing(ush, &command[ush->k][ush->triger]);
            if (copy) {
                pipemat[ush->i][j] = mx_strdup(copy);
                mx_strdel(&copy);
            }
            else
                pipemat[ush->i][j] = pipe_parsing(ush,
                                                &command[ush->k][ush->triger]);
        }
    }
}

static void pipe_matrix_filling(t_ush *ush, char ***pipemat, char **command,
                                                            int pipemat_size) {
    int i_count = 0;
    int j_count = 0;
    int commat_size = 0;

    ush->size = mx_strarrlen(command);
    for (ush->i = 0; ush->i <  pipemat_size; ush->i++) {
        commat_size = mx_size_of_pipe_matstr(command, &i_count, &j_count);
        pipemat[ush->i] = (char **)malloc(sizeof(char *) * (commat_size + 1));
        if (mx_strcmp(command[ush->k], "|") == 0 || command[ush->k] == NULL)
            ush->k++;
        filling_cycle(ush, pipemat, command, commat_size);
        pipemat[ush->i][commat_size] = NULL;
    }
}

char ***mx_pipe_matrix_creation(t_ush *ush, char **command) {
    int pipemat_size = mx_count_pipes(command);
    char ***pipemat = NULL;

    if (pipemat_size == 0) {
        mx_printerr("ush: parse error near `|'\n");
        return NULL;
    }
    pipemat = (char ***)malloc(sizeof(char **) * (pipemat_size + 1));
    pipemat[pipemat_size] = NULL;
    pipe_matrix_filling(ush, pipemat, command, pipemat_size);
    ush->i = 0;
    ush->k = 0;
    ush->size = 0;
    ush->triger = 0;
    return pipemat;
}
