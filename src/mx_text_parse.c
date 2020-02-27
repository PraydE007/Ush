#include "ush.h"

char *mx_text_parse(char *str, int *piv) {
    char *res = NULL;
    int i = 1;

    while (str) {
        if (str[i] == ' ' || str[i] == '\\'
            || str[i] == '\'' || str[i] == '\"'
            || str[i] == '$' || str[i] == '\0') {
            res = mx_strnew_x(i);
            strncpy(res, &str[0], i);
            break;
        }
        i++;
    }
    (*piv) += (i - 1);
    return res;
}
