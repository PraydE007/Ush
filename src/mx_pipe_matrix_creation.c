#include "../inc/ush.h"

static bool is_not_a_pipe(char **comn, int i, int j) {
    if (comn[i][j] == '|' && ((!comn[i][j + 1] && (!comn[i + 1]
        || (comn[i + 1] && (mx_strcmp(comn[i + 1], "|") == 0
        || comn[i + 1][0] == '|'))))
        || (comn[i][j + 1] == '|' && comn[i][j + 2] == '|')))
        return true;
    return false;
}

static bool is_diuble_pipe(char **comn, int i, int j) {
    if (comn[i][j] == '|' && comn[i][j + 1] == '|'
        && ((comn[i][j + 2] && comn[i][j + 2] != '|')
        || (comn[i + 1] && mx_strcmp(comn[i + 1], "|") != 0
        && comn[i + 1][0] != '|')))
        return true;
    return false;
}

static int count_pipes(char **comn) {
    int count = 1;

    if (mx_strcmp(comn[0], "|") == 0 || comn[0][0] == '|')
        return 0;
    for (int i = 0; comn[i]; i++) {
        if (mx_strcmp(comn[i], "|") == 0 && (comn[i + 1]
            && mx_strcmp(comn[i + 1], "|") == 0))
            return 0;
        for (int j = 0; comn[i][j]; j++) {
            if (is_not_a_pipe(comn, i, j))
                return 0;
            else if (is_diuble_pipe(comn, i, j))
                return count;
            else if (comn[i][j] == '|')
                count++;
        }
    }    
    return count;
}

static void condition_for_matstr(char **comn, int *i, int *j, int *size) {
    if ((*j) == 0 && comn[(*i)][1])
        (*size)--;
    if (comn[(*i)][(*j) + 1])
        (*j)++;
    else if (comn[(*i) + 1]) {
    (*i)++;
    (*j) = 0;
    }
}

static int size_of_matstr(char **comn, int *i, int *j) {
    int size = 0;

    for (; comn[(*i)]; (*i)++) {
        if (mx_strcmp(comn[(*i)], "|") != 0)
            size++;
        for (; comn[(*i)][(*j)]; (*j)++) {
            if (comn[(*i)][(*j)] == '|') {
                condition_for_matstr(comn, i, j, &size);
                return size;
            }
        }
        (*j) = 0;
    }    
    return size;
}

static char *pipe_parsing(char *command, int *k, int *triger) {
    int size = 0;
    int i = 0;
    char *pipemat = NULL;

    for (; command[i]; i++, (*triger)++) {
        if (command[i] == '|')
            break;
        size++;
    }
    if (size > 0) 
        pipemat = mx_strndup(command, size);
    if (command[i + 1]) 
        (*triger)++;
    else {
        (*triger) = 0;
        (*k)++;
    }
    return pipemat;
}

char ***mx_pipe_matrix_creation(t_ush *ush, char **command) {
    int i_count = 0;
    int j_count = 0;
    int commat_size = 0;
    int pipemat_size = count_pipes(command);
    char ***pipemat = NULL;
    int k = 0;
    int triger = 0;

    if (pipemat_size == 0) {
        mx_printerr("ush: parse error near `|'\n");
        return NULL;
    }
    pipemat = (char ***)malloc(sizeof(char **) * (pipemat_size + 1));
    pipemat[pipemat_size] = NULL;
    for (ush->i = 0; ush->i <  pipemat_size; ush->i++) {
        commat_size = size_of_matstr(command, &i_count, &j_count);
        pipemat[ush->i] = (char **)malloc(sizeof(char *) * (commat_size + 1));
        if (mx_strcmp(command[k], "|") == 0 || command[k] == NULL)
            k++;
        for (int j = 0; j < commat_size; j++) {
            if (!mx_is_pipe(NULL, &command[k][triger])) {
                pipemat[ush->i][j] = mx_strdup(&command[k][triger]);
                k++;
                triger = 0;
            }
            else {
                char *copy = pipe_parsing(&command[k][triger], &k, &triger);
                    
                if (copy) {
                    pipemat[ush->i][j] = mx_strdup(copy);
                    mx_strdel(&copy);    
                }
                else
                    pipemat[ush->i][j] = pipe_parsing(&command[k][triger], &k, &triger);   
                break;
            }
        }
        pipemat[ush->i][commat_size] = NULL;
    }
    ush->i = 0;
    return pipemat;
}
