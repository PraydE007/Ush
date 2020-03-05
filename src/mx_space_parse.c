#include "ush.h"

char *mx_space_parse(char *str, int *piv) {
    char *res = NULL;
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        if (str[i] != ' ' || str[i] == '\0') {
            res = mx_strnew_x(2);
            res[0] = ' ';
            break;
        }
        i++;
    }
    (*piv) += (i - 1);
    return res;
}
