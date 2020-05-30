#include "../inc/ush.h"

int mx_three_slash_m(char **res, char *str, int *i, int *res_size) {
    (*i) += 3;
    if (str[(*i)] == '\0' || str[(*i)] == '\"') {
        return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else {
        mx_push_symbol(res, '\\', res_size);
        mx_push_symbol(res, '\\', res_size);
        return mx_push_symbol(res, str[(*i)], res_size);
    }
}
