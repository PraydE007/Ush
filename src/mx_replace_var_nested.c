#include "../inc/ush.h"

void mx_replace_var_nested(t_ush *ush, char **res, char **var) {
    char *result = mx_get_variable(ush, *var);

    mx_strdel(var);
    (*res) = mx_strjoin_free(*res, result);
    mx_strdel(&result);
}
