#include "../inc/ush.h"

int mx_one_slash_s(char **res, char *str, int *i) {
    int res_size = mx_strlen(*res) + 1;

    (*i) += 1;
    if (str[(*i)] == '\0') {
        (*i) -= 1;
        return 0;
    }
    else {
        mx_push_symbol(res, '\\', &res_size);
        return mx_push_symbol(res, str[(*i)], &res_size);
    }
}
