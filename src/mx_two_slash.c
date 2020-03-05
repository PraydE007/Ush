#include "../inc/ush.h"

int mx_two_slash(char **res, char *str, int *i, int *res_size) {
    (*i) += 2;
    if (str[(*i)] == '\0' || str[(*i)] == ' '
        || str[(*i)] == '\'' || str[(*i)] == '\"') {
        (*i) -= 1;
        return mx_push_symbol(res, '\\', res_size);
    }
    else if (mx_control_slash(res, &str[1], res_size))
        return 1;
    else {
        mx_push_symbol(res, '\\', res_size);
        return mx_push_symbol(res, str[(*i)], res_size);
    }
}
