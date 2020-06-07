#include "../inc/ush.h"

void mx_replace_subst_nested(t_ush *ush, char **res, char **var) {
    char *executed = mx_substitution_making(ush, *var);

    mx_strdel(var);
    if (!executed)
        executed = mx_strnew_x(1);
    (*res) = mx_strjoin_free(*res, executed);
    mx_strdel(&executed);
}
