#include "../inc/ush.h"
//CHECK COMMENTS
int mx_four_slash_sinmrk(char **res, char *str, int *i) {
    str = str + 1 - 1; // wa for unused var
    (*i) += 3;
    mx_push_symbol_l(res, '\\');
    mx_push_symbol_l(res, '\\');
    mx_push_symbol_l(res, '\\');
    return mx_push_symbol_l(res, '\\');
}
