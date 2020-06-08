#include "../inc/ush.h"

int mx_control_slash(char **res, char ch) {
    int trg = 0;

    if (ch == 'a')
        trg = mx_push_symbol_l(res, '\a');
    else if (ch == '0')
        trg = 1;
    else if (ch == 'b')
        trg = mx_push_symbol_l(res, '\b');
    else if (ch == 't')
        trg = mx_push_symbol_l(res, '\t');
    else if (ch == 'n')
        trg = mx_push_symbol_l(res, '\n');
    else if (ch == 'v')
        trg = mx_push_symbol_l(res, '\v');
    else if (ch == 'f')
        trg = mx_push_symbol_l(res, '\f');
    else if (ch == 'r')
        trg = mx_push_symbol_l(res, '\r');
    return trg;
}
