#include "../inc/ush.h"

static void close_out(int *pipedes) {
    close(pipedes[0]);
    dup2(pipedes[1], 1);
    close(pipedes[1]);
}

void mx_pipe_process_creator(t_ush *ush, char ***commat) {
    int pipedes[2];

    if (commat[1]) {
        pipe(pipedes);
        ush->pid1 = fork();
        ush->pid2 = ush->pid1;
        if (ush->pid1 == 0) {
            close_out(pipedes);
            mx_child_process(ush, commat[ush->i]);
        }
        else if (ush->pid1 < 0)
            perror("ush");
        else if (ush->pid1 > 0 )
            mx_pipe_parent_process(ush, commat, pipedes);
    }
    else
        mx_is_builtin(ush, commat[0]) ? 0 : mx_process_creator(ush, commat[0]);
    ush->i = 0;
    ush->pid1 = 0;
    ush->pid2 = 0;
}
