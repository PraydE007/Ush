#include "../inc/ush.h"

int mx_four_slash_sinmrk(char **res, char *str, int *i) {
    int res_size = mx_strlen(*res) + 1;

    (*i) += 3;
    mx_push_symbol(res, '\\', &res_size);
    mx_push_symbol(res, '\\', &res_size);
    mx_push_symbol(res, '\\', &res_size);
    return mx_push_symbol(res, '\\', &res_size);
}
