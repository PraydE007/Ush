#include "../inc/ush.h"

int mx_doumrk_subst(t_ush *ush, char **res, char *str, int *piv) {
    char *sub = mx_strnew_x(1);
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0')
            return mx_break_on_error(&sub) == NULL ? 0 : 0;
        else if (str[i] == '`')
            break;
        else if (str[i] == '\\') {
            mx_subst_slash_parse(&sub, &str[i], &i);
        }
        else
            mx_push_symbol_l(&sub, str[i]);
        i++;
    }
    mx_replace_subst_nested(ush, res, &sub);
    (*piv) += i + 1;
    return 1;
}
