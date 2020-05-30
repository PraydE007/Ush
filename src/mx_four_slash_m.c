#include "../inc/ush.h"

int mx_four_slash_m(char **res, char *str, int *i, int *res_size) {
    (*i) += 3;
    mx_push_symbol(res, '\\', res_size);
    return mx_push_symbol(res, '\\', res_size);
}
