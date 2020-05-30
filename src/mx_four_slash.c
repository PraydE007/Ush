#include "../inc/ush.h"

int mx_four_slash(char **res, char *str, int *i) {
    int res_size = mx_strlen(*res) + 1;

    (*i) += 4;
    mx_push_symbol(res, '\\', &res_size);
    mx_push_symbol(res, '\\', &res_size);
    return mx_push_symbol(res, str[(*i)], &res_size);
}
