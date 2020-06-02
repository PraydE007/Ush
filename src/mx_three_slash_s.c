#include "../inc/ush.h"

int mx_three_slash_s(char **res, char *str, int *i) {
    (*i) += 3;
    if (str[(*i)] == '\0') {
        (*i) -= 1;
        return 0;
    }
    else {
        mx_push_symbol_l(res, '\\');
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
