#include "../inc/ush.h"

int mx_three_slash(char **res, char *str, int *i) {
    (*i) += 3;
    if (str[(*i)] == '\0') {
        return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    // else if (mx_control_slash(res, &str[2], &res_size))
    //     return 1;
    else {
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
