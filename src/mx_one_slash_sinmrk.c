#include "../inc/ush.h"

int mx_one_slash_sinmrk(char **res, char *str, int *i) {
    (*i) += 1;
    if (str[(*i)] == '\0')
        return mx_break_on_error(res) == NULL ? 0 : 0;
    else if (str[(*i)] == '\'') {
        (*i) -= 1;
        return mx_push_symbol_l(res, '\\');
    }
    else {
        // (*i) -= 1;
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
