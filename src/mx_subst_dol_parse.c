#include "../inc/ush.h"

char *mx_subst_dol_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int res_size = 1;
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0')
            return mx_break_on_error(&res);
        else if (str[i] == ')')
            break;
        else
            mx_push_symbol(&res, str[i], &res_size);
        i++;
    }
    (*type) = 3;
    (*piv) += i + 2;
    return res;
}
