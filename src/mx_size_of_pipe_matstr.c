#include "../inc/ush.h"

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

int mx_size_of_pipe_matstr(char **comn, int *i, int *j) {
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
