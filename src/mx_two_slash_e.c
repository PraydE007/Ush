#include "../inc/ush.h"

int mx_two_slash_e(char **res, char *str, int *i) {
    (*i) += 2;
    mx_push_symbol_l(res, '\\');
    return mx_push_symbol_l(res, str[(*i)]);
}
