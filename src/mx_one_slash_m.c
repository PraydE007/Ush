#include "../inc/ush.h"

int mx_one_slash_m(char **res, char *str, int *i) {
    (*i) += 1;
    if (str[(*i)] == '\0' || str[(*i)] == '\"') {
        // (*i) -= 1; # Extra line due to error!
        return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else {
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
