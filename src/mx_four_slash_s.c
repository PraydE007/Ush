#include "../inc/ush.h"

int mx_four_slash_s(char **res, char *str, int *i) {
    int res_size = mx_strlen(*res) + 1;

    (*i) += 3;
    return mx_push_symbol(res, '\\', &res_size);
}
