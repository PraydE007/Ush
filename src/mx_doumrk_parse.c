#include "ush.h"

static bool count_slashes(char *str, int *i, int *sl) {
    while (str[(*i)] != '\0') {
        if (str[(*i)] == '\"') {
            if (str[(*i) - 1] == '\\')
                (*sl) += 1;
            else
                return true;
        }
        (*i) += 1;
    }
    return false;
}

static void copy_source(char *res, char *str, int *i, int *j) {
    for ((*i) = 1; str[(*i)] != '\0' && res != NULL; (*i) += 1) {
        if (str[(*i)] == '\"') {
            if (str[(*i) - 1] == '\\')
                res[(*j) - 1] = '\"';
            else
                break;
        }
        else {
            res[(*j)] = str[(*i)];
            (*j) += 1;
        }
    }
    // res[(*j) += 1] = '\0';
}

char *mx_doumrk_parse(char *str, int *piv) {
    char *res = NULL;
    int i = 1;
    int j = 0;
    int sl = 0;

    if (mx_strlen(str) <= 0)
        return NULL;
    if (!count_slashes(str, &i, &sl))
        return NULL;
    res = mx_strnew_x(i - sl);
    copy_source(res, str, &i, &j);
    (*piv) += (i - 1);
    return res;
}
