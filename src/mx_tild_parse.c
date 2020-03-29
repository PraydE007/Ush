#include "../inc/ush.h"

char *mx_tild_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int res_size = 1;

    (*type) = 2;
    if (str[0] == '+')
        mx_push_symbol(&res, '+', &res_size);
    else if (str[0] == '-')
        mx_push_symbol(&res, '-', &res_size);
    (*piv) += res_size - 1;
    return res;
}
