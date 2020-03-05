#include "../inc/ush.h"

int mx_one_slash(char **res, char *str, int *i, int *res_size) {
    (*i) += 1;
    if (str[(*i)] == '\0')
        return mx_break_on_error(res) == NULL ? 0 : 0;
    else
        return mx_push_symbol(res, str[(*i)], res_size);
}
