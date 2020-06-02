#include "../inc/ush.h"

int mx_four_slash_s(char **res, char *str, int *i) {
    (*i) += 3;
    return mx_push_symbol_l(res, '\\');
}
