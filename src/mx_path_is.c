#include "../inc/ush.h"

bool mx_path_is (t_ush *ush) {
    t_variable *pl = ush->variable_list;

    if (getenv("PATH") != 0)
        return true;
    else {
        while (pl) {
            if (mx_strcmp("PATH", pl->key) == 0)
                return true;
            pl = pl->next;
        }
    }
    return false;
}
