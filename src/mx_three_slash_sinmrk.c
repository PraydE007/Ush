#include "../inc/ush.h"

int mx_three_slash_sinmrk(char **res, char *str, int *i) {
    int res_size = mx_strlen(*res) + 1;

    (*i) += 3;
    if (str[(*i)] == '\0') {
        (*i) -= 1;
        return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (str[(*i)] == '\'') {
        (*i) -= 1;
        mx_push_symbol(res, '\\', &res_size);
        mx_push_symbol(res, '\\', &res_size);
        return mx_push_symbol(res, '\\', &res_size);
    }
    // else if (mx_control_slash(res, &str[2], &res_size))
    //     return 1;
    else {
        mx_push_symbol(res, '\\', &res_size);
        mx_push_symbol(res, '\\', &res_size);
        mx_push_symbol(res, '\\', &res_size);
        return mx_push_symbol(res, str[(*i)], &res_size);
    }
}
