#include "../inc/ush.h"

static int subst_dol_parse(char **res, char *str, int *piv) {
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0')
            return 0;
        else if (str[i] == ')')
            break;
        else
            mx_push_symbol_l(res, str[i]);
        i++;
    }
    (*piv) += i + 2;
    return 1;
}

static int quote_dol_parse(char **res, char *str, int *piv) {
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0' || str[i] == ' ' || str[i] == '\"'
            || str[i] == '\\' || str[i] == '`')
            return 0;
        else if (str[i] == '}')
            break;
        else
            mx_push_symbol_l(res, str[i]);
        i++;
    }
    (*piv) += i + 2;
    return 1;
}

static int def_dol_parse(char **res, char *str, int *piv) {
    int len = mx_strlen(str);
    int i = 0;

    while (i <= len) {
        if (str[i] == '\0' || str[i] == ' ' || str[i] == '\"'
            || str[i] == '\\' || str[i] == '`' || str[i] == ',')
            break;
        else if (str[i] == '$' && mx_strlen(*res) > 1)
            break;
        else
            mx_push_symbol_l(res, str[i]);
        i++;
    }
    (*piv) += i;
    return 1;
}

static bool is_correct(char **res, char *str) {
    if (str[0] == '\0' || str[0] == ' ' || str[0] == '\"'
        || str[0] == '\\' || str[0] == '`') {
        mx_push_symbol_l(res, '$');
        return false;
    }
    return true;
}

int mx_doumrk_dollar(t_ush *ush, char **res, char *str, int *piv) {
    char *dol = mx_strnew_x(1);

    if (!is_correct(res, str))
        return mx_break_on_error(&dol) == NULL ? 1 : 1;
    if (str[0] == '(') {
        if (!subst_dol_parse(&dol, &str[1], piv))
            return mx_break_on_error(&dol) == NULL ? 0 : 0;
        mx_replace_subst_nested(ush, res, &dol);
        return 1;
    }
    if (str[0] == '{') {
        if (!quote_dol_parse(&dol, &str[1], piv))
            return mx_break_on_error(&dol) == NULL ? 0 : 0;
    }
    else {
        if (!def_dol_parse(&dol, str, piv))
            return mx_break_on_error(&dol) == NULL ? 0 : 0;
    }
    mx_replace_var_nested(ush, res, &dol);
    return 1;
}
