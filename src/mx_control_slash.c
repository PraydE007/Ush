#include "../inc/ush.h"

bool mx_control_slash(char **res, char *str, int *res_size) {
    bool trg = 0;

    if (str[1] == 'a')
        trg = mx_push_symbol(res, '\a', res_size);
    else if (str[1] == '0')
        trg = 1;
    else if (str[1] == 'b')
        trg = mx_push_symbol(res, '\b', res_size);
    else if (str[1] == 't')
        trg = mx_push_symbol(res, '\t', res_size);
    else if (str[1] == 'n')
        trg = mx_push_symbol(res, '\n', res_size);
    else if (str[1] == 'v')
        trg = mx_push_symbol(res, '\v', res_size);
    else if (str[1] == 'f')
        trg = mx_push_symbol(res, '\f', res_size);
    else if (str[1] == 'r')
        trg = mx_push_symbol(res, '\r', res_size);
    return trg;
}
