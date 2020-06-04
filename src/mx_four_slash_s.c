#include "../inc/ush.h"

int mx_four_slash_s(char **res, char *str, int *i) {
    str = str + 1 - 1; // wa for unused var
    (*i) += 3;
    return mx_push_symbol_l(res, '\\');
}
