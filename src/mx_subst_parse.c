#include "../inc/ush.h"

char *mx_subst_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int res_size = 1;
    int i = 0;

    while (i <= mx_strlen(str)) {
        if (str[i] == '\0')
            return mx_break_on_error(&res);
        else if (str[i] == '`')
            break;
        else if (str[i] == '\\') {
            mx_subst_slash_parse(&res, &str[i], &i);
        }
        else {
            res_size = mx_strlen(res) + 1;
            mx_push_symbol(&res, str[i], &res_size);
        }
        i++;
    }
    (*type) = 3;
    (*piv) += i + 1;
    return res;
}
