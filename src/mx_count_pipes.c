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

int mx_count_pipes(char **comn) {
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
