#include "../inc/ush.h"

int mx_four_slash_e(char **res, int *i) {
    (*i) += 3;
    mx_push_symbol_l(res, '\\');
    return mx_push_symbol_l(res, '\\');
}
