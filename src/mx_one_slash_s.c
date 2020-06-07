#include "../inc/ush.h"

int mx_one_slash_s(char **res, char *str, int *i) {
    (*i) += 1;
    if (str[(*i)] == '\0') {
        (*i) -= 1;
        return 0;
    }
    else {
        return mx_push_symbol_l(res, str[(*i)]);
    }
}
