#include "ush.h"

static void slash_handling(char **res, char *str, int *i, int *res_size) {
    if (str[1] == '\0')
        return;
    else if (str[1] == '\'') {
        mx_push_symbol(res, '\\', res_size);
    }
    else if (mx_control_slash(res, str, res_size)) {
        (*i) += 1;
        return;
    }
    else {
        mx_push_symbol(res, str[1], res_size);
        (*i) += 1;
    }
}

char *mx_sinmrk_parse(char *str, int *piv) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int res_size = 1;
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0')
            return mx_break_on_error(&res);
        else if (str[i] == '\\')
            slash_handling(&res, &str[i], &i, &res_size);
        else if (str[i] == '\'')
            break;
        else
            mx_push_symbol(&res, str[i], &res_size);
        i++;
    }
    (*piv) += i + 1;
    return res;
}
