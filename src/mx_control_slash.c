#include "../inc/ush.h"

bool mx_control_slash(char **res, char *str) {
    bool trg = 0;

    if (str[1] == 'a')
        trg = mx_push_symbol_l(res, '\a');
    else if (str[1] == '0')
        trg = 1;
    else if (str[1] == 'b')
        trg = mx_push_symbol_l(res, '\b');
    else if (str[1] == 't')
        trg = mx_push_symbol_l(res, '\t');
    else if (str[1] == 'n')
        trg = mx_push_symbol_l(res, '\n');
    else if (str[1] == 'v')
        trg = mx_push_symbol_l(res, '\v');
    else if (str[1] == 'f')
        trg = mx_push_symbol_l(res, '\f');
    else if (str[1] == 'r')
        trg = mx_push_symbol_l(res, '\r');
    return trg;
}
