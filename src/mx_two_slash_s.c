#include "../inc/ush.h"

int mx_two_slash_s(char **res, char *str, int *i) {
    (*i) += 2;
    if (str[(*i)] == '\0' || str[(*i)] == '`') {
        (*i) -= 1;
        return 0;
    }
    else
        return mx_push_symbol_l(res, str[(*i)]);
}
