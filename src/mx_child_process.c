#include "../inc/ush.h"

static bool is_path(t_variable **list) {
    t_variable *pl = *list;

    while (pl) {
        if (mx_strcmp("PATH", pl->key) == 0)
            return true;
        pl = pl->next;
    }
    return false;
}

void mx_child_process(t_ush *ush, char **command) {
    char *proga = NULL;

    proga = mx_programm_finder(command[0]);
    if (getenv("PATH") != 0) {
        if (execvp(command[0], command) == -1)
            mx_error_making(command[0]);
    }
    else {
        if (is_path(&ush->variable_list) && proga) {
            mx_strdel(&command[0]);
            command[0] = mx_strdup(proga);
            mx_strdel(&proga);
        }
        if (execv(command[0], command) == -1)
            mx_error_making(command[0]);
    }
    exit(EXIT_FAILURE);
}
