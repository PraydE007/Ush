#include "ush.h"

char *mx_text_parse(char *str, int *piv) {
    char *res = NULL;
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
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
