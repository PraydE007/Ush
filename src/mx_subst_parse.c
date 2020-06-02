#include "../inc/ush.h"

char *mx_subst_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int i = 0;

    while (i <= mx_strlen(str)) {
        if (str[i] == '\0')
            return mx_break_on_error(&res);
        else if (str[i] == '`')
            break;
        else if (str[i] == '\\') {
            mx_subst_slash_parse(&res, &str[i], &i);
        }
        else
            mx_push_symbol_l(&res, str[i]);
        i++;
    }
    (*type) = 3;
    (*piv) += i + 1;
    return res;
}
