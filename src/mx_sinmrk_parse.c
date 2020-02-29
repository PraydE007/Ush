#include "ush.h"

char *mx_sinmrk_parse(char *str, int *piv) {
    char *res = NULL;
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        // OTHER CASES
        if (str[i] == '\0')
            break;
        if (str[i] == '\'') {
            res = mx_strnew_x(i);
            strncpy(res, &str[0], i);
            break;
        }
        i++;
    }
    (*piv) += i + 1;
    return res;
}
