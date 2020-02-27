#include "ush.h"

char *mx_sinmrk_parse(char *str, int *piv) {
    char *res = NULL;
    int i = 1;

    while (str[i] != '\0') {
        if (str[i] == '\'') {
            res = mx_strnew_x(i);
            strncpy(res, &str[1], i - 1);
        }
        i++;
    }
    (*piv) += (i - 1);
    return res;
}
