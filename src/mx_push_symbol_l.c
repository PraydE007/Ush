#include "../inc/ush.h"

int mx_push_symbol_l(char **res, char ch) {
    int res_size = mx_strlen(*res) + 1;

    res_size += 1;
    (*res) = (char *)realloc((*res), res_size);
    (*res)[res_size - 1] = '\0';
    (*res)[res_size - 2] = ch;
    return 1;
}
