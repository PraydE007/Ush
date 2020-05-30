#include "../inc/ush.h"

int mx_one_slash_m(char **res, char *str, int *i, int *res_size) {
    (*i) += 1;
    if (str[(*i)] == '\0' || str[(*i)] == '\"') {
        // (*i) -= 1; # Extra line due to error!
        return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else {
        mx_push_symbol(res, '\\', res_size);
        return mx_push_symbol(res, str[(*i)], res_size);
    }
}
