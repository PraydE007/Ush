#include "../inc/ush.h"

static void cntrl_z_printing(char ***commat) {
    mx_printstr("\nush: suspended  ");
    for (int i = 0; commat[i]; i++) {
        for (int j = 0; commat[i][j]; j++) {
            mx_printstr(commat[i][j]);
            if (commat[i][j + 1])
                mx_printstr(" ");
        }
        if (commat[i + 1])
            mx_printstr(" | ");
    }
    mx_printstr("\n");
}

static void error_status(t_ush *ush, int status) {
    if (status == 256)
        ush->exit_code = 1;
    else if (WEXITSTATUS(status))
        ush->exit_code = 127;
    else
        ush->exit_code = 0;
}

void mx_signal_end(t_ush *ush, char ***commat, int status, int *buf_exit) {
    if (WIFEXITED(status))
        error_status(ush, status);
    else if (WIFSTOPPED(status)) {
        ush->exit_code = 146;
        mx_push_jobs_node(&ush->jobs_list, &ush->pid_list, NULL, commat);
        cntrl_z_printing(commat);
    }
    else if (WTERMSIG(status)) {
        ush->exit_code = 130;
        mx_printstr("\n");
    }
    else if (status != 0)
        ush->exit_code = 1;
    if (ush->triger == 0)
        (*buf_exit) = ush->exit_code;
    ush->exit_code = (*buf_exit);
    ush->triger++;
}
