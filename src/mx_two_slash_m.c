#include "../inc/ush.h"

int mx_two_slash_m(char **res, char *str, int *i) {
    (*i) += 2;
    if (str[(*i)] == '\0')
        return mx_break_on_error(res) == NULL ? 0 : 0;
    else if (str[(*i)] == '\"') {
        (*i) -= 1;
        return mx_push_symbol_l(res, '\\');
    }
    else {
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
