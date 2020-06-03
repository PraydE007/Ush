#include "../inc/ush.h"

static void close_out(int *pipedes) {
    close(pipedes[0]);
    dup2(pipedes[1], 1);
    close(pipedes[1]);
}

static void ush_zeroing(t_ush *ush) {
    if (ush->exit_code != 146) {
        while (ush->pid_list)
            mx_pop_front_pid(&ush->pid_list);
    }
    ush->i = 0;
    ush->pid1 = 0;
    ush->pid2 = 0;
    ush->triger = 0;
}

void mx_pipe_process_creator(t_ush *ush, char ***commat) {
    int pipedes[2];
    int buf_exit = 0;
    
    ush->pid_list = NULL;
    if (commat[1]) {
        pipe(pipedes);
        ush->pid1 = fork();
        ush->pid2 = ush->pid1;
        if (ush->pid1 == 0) {
            close_out(pipedes);
            mx_child_process(ush, commat[ush->i]);
        }
        else if (ush->pid1 > 0 )
            mx_pipe_parent_process(ush, commat, pipedes, &buf_exit);
    }
    else
        mx_is_builtin(ush, commat[0]) ? 0 : mx_process_creator(ush, commat[0]);
    ush_zeroing(ush);
}
