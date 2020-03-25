#include "../inc/ush.h"

char *get_another(t_ush *ush, char *var_name) {
    if (mx_strcmp(var_name, "?") == 0)
        return mx_itoa(ush->exit_code);
    return NULL;
}

char *get_from_ush(t_ush *ush, char *var_name) {
    t_variable *p = ush->variable_list;

    while (p) {
        if (mx_strcmp(p->key, var_name) == 0)
            return p->value;
        p = p->next;
    }
    return NULL;
}

char *mx_get_variable(t_ush *ush, char *var_name) {
    char *res = NULL;
    char *value = NULL;

    if ((value = get_from_ush(ush, var_name)) != NULL)
        res = mx_strdup_x(value);
    else if ((value = getenv(var_name)) != NULL)
        res = mx_strdup_x(value);
    else if ((value = get_another(ush, var_name)) != NULL)
        res = value;
    else
        res = mx_strnew_x(1);
    return res;
}
