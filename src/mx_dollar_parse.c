#include "../inc/ush.h"

static char *quote_dol_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int res_size = 1;
    int i = 0;

    (*type) = 1;
    while (i <= len) {
        if (str[i] == '\0' || str[i] == '\''
            || str[i] == '\"' || str[i] == ' ')
            return mx_break_on_error(&res);
        else if (str[i] == '}')
            break;
        else
            mx_push_symbol(&res, str[i], &res_size);
        i += 1;
    }
    (*piv) += i + 2;
    return res;
}

static int def_handling(char **res, char *str, int *i, int *res_size) {
    if (str[(*i)] == '\'' || str[(*i)] == '\"')
        return 1;
    else if (str[(*i)] == '$' && (*res_size) > 1)
        return 1;
    else if (str[(*i)] == '\0' || str[(*i)] == ' ') {
        if ((*res_size) > 1)
            return 1;
        else
            mx_push_symbol(res, '$', res_size);
        return 0;
    }
    else
        mx_push_symbol(res, str[(*i)], res_size);
    (*i) += 1;
    return -1;
}

static char *def_dol_parse(char *str, int *piv, int *type) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int res_size = 1;
    int hand_res = 0;
    int i = 0;

    while (i <= len) {
        if ((hand_res = def_handling(&res, str, &i, &res_size)) != -1) {
            if (hand_res == 1)
                (*type) = 1;
            else
                (*type) = 0;
            break;
        }
    }
    (*piv) += i;
    return res;
}

char *mx_dollar_parse(char *str, int *piv, int *type) {
    if (str[0] == '{')
        return quote_dol_parse(&str[1], piv, type);
    return def_dol_parse(str, piv, type);
}
