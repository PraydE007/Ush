#include "../inc/ush.h"
// A LOT OF LINES
bool mx_isvariable (t_ush *ush, char **k_v) {
    t_variable *pl = ush->variable_list;

    if (getenv(k_v[0]) != 0) {
        if (k_v[1] != NULL)
            setenv(k_v[0], k_v[1], 1);
        else
            setenv(k_v[0], "", 1);
        ush->trigger = true;
    }
    while (pl) {
        if (mx_strcmp(k_v[0], pl->key) == 0) {
            if (k_v[1] != NULL) {
                mx_strdel(&pl->value);
                pl->value = mx_strdup(k_v[1]);
            }
            else
                mx_strdel(&pl->value);
            return false;
        }
        pl = pl->next;;
    }
    return true;
}
