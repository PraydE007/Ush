#include "../inc/ush.h"

static bool is_null(char **command) {
    int size = mx_strarrlen(command);

    for (int i = 1; i < size; i++) {
        if (mx_strcmp(command[i], "\0") != 0)
            return false;
    }
    return true;
}

void mx_fg(t_ush *ush, char **command) {
    t_jobs *pl_jobs = ush->jobs_list;
    int lenth = mx_jobs_list_len(&ush->jobs_list);

    if (pl_jobs == NULL) {
        mx_printerr("fg: no current job\n");
        ush->exit_code = 1;
        return;
    }
    else if (mx_strarrlen(command) == 1 || is_null(command)) {
        while (pl_jobs) {
            if (pl_jobs->sign == '+')
                break;
            pl_jobs = pl_jobs->next;
        }
        if (pl_jobs)
            mx_fg_signal(ush, &pl_jobs, lenth);
    }
    else if (mx_strarrlen(command) > 1)
        mx_fg_command_handler(ush, &pl_jobs, command, lenth);
}
