#include "../inc/ush.h"

static bool count_slashes(char *str, int *i, int *sl) {
    int len = mx_strlen(str);

    while ((*i) <= len) {
        if (str[(*i)] == '\0')
            break;
        // OTHER CASES
        if (str[(*i)] == '\"' && str[(*i) - 1] != '\\')
            return true;
        (*i) += 1;
    }
    return false;
}

static void copy_source(char *res, char *str, int *i) {
    int len = mx_strlen(str);
    int k = 0;

    // i = 0 here       \/
    for (int j = 0, k = 0; k <= len /*&& res*/; k += 1) {
        // OTHER CASES
        if (str[k] == '\"' && str[k - 1] != '\\')
            break;
        else {
            res[j] = str[k];
            j += 1;
        }
    }
    (*i) = k;
}

char *mx_doumrk_parse(char *str, int *piv) {
    char *res = NULL;
    int len = mx_strlen(str);
    int i = 0;
    int sl = 0;

    if (!count_slashes(str, &i, &sl))
        return NULL;
    res = mx_strnew_x(i - sl);
    copy_source(res, str, &i);
    (*piv) += i + 1;
    return res;
}
