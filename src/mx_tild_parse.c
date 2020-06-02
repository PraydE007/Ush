#include "../inc/ush.h"

char *mx_tild_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);

    (*type) = 2;
    if (str[0] == '+')
        mx_push_symbol_l(&res, '+');
    else if (str[0] == '-')
        mx_push_symbol_l(&res, '-');
    (*piv) += mx_strlen(res); // res_size - 1 before
    return res;
}
