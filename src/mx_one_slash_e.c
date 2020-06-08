#include "../inc/ush.h"

int mx_one_slash_e(char **res, char *str, int *i) {
    (*i) += 1;
    if (mx_is_control_slash(str[(*i)]))
        return mx_control_slash(res, str[(*i)]);
    else {
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
