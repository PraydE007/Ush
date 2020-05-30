#include "../inc/ush.h"

int mx_two_slash_s(char **res, char *str, int *i) {
    int res_size = mx_strlen(*res) + 1;

    (*i) += 2;
    if (str[(*i)] == '\0' || str[(*i)] == '`') {
        (*i) -= 1;
        return 0;
    }
    else
        return mx_push_symbol(res, str[(*i)], &res_size);
}
