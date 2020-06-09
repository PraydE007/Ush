#include "../inc/ush.h"

int mx_four_slash(char **res, char *str, int *i) {
    (*i) += 4;
    mx_push_symbol_l(res, '\\');
    mx_push_symbol_l(res, '\\');
    return mx_push_symbol_l(res, str[(*i)]);
}
