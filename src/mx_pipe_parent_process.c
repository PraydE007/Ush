#include "../inc/ush.h"

static void child_recursion(t_ush *ush, char ***commatrix, int *pipedes,
                                                            int *pipedes2) {
    dup2(pipedes[0], 0);
    close(pipedes[0]);
    if (commatrix[ush->i + 1]) {
        close(pipedes2[0]);
        dup2(pipedes2[1], 1);
        close(pipedes2[1]);
    }
    mx_child_process(ush, commatrix[ush->i]);
}

static bool recursion_checking(char ***commatrix) {
    if (mx_strcmp(commatrix[0][0], "cat") == 0)
        return true;
    for (int i = 0; commatrix[i]; i++) {
        if (commatrix[i][1]) {
            for (int j = 0; commatrix[i][1][j]; j++) {
                if (mx_strcmp(commatrix[i][0], "ls") == 0
                    && commatrix[i][1][j] == 'R')
                    return true;
            }
        }
    }
    return false;
}

static void pipe_creator(t_ush *ush, char ***commatrix, int *pipedes,
                                                            int *buf_exit) {
    int pipedes2[2];

    ush->pid1 = 0;
    ush->i = ush->i + 1;
    close(pipedes[1]);
    pipe(pipedes2);
    ush->pid1 = fork();
    if (ush->pid1 == 0)
        child_recursion(ush, commatrix, pipedes, pipedes2);
    else if (ush->pid1 < 0)
        perror("ush");
    else if (ush->pid1 > 0)
        mx_pipe_parent_process(ush, commatrix, pipedes2, buf_exit);
}

static void wait_pipe(t_ush *ush, char ***commat, int *pipedes,
                                                            int *buf_exit) {
    int status = 0;
    pid_t wpid = 0;

    wpid = waitpid(ush->pid1, &status, WUNTRACED);
    if (commat[ush->i + 1])
        pipe_creator(ush, commat, pipedes, buf_exit);
}

void mx_pipe_parent_process(t_ush *ush, char ***commat, int *pipedes,
                                                            int *buf_exit) {
    int status = 0;
    pid_t wpid = 0;

    mx_push_back_pid(&ush->pid_list, ush->pid1);
    setpgid(ush->pid1, ush->pid2);
    tcsetpgrp(1, ush->pid2);
    if (recursion_checking(commat)) {
        if (commat[ush->i + 1])
            pipe_creator(ush, commat, pipedes, buf_exit);
        else if (mx_strcmp(commat[0][0], "cat") == 0)
            wpid = waitpid(ush->pid2, &status, WUNTRACED);
        else
            wpid = waitpid(ush->pid1, &status, WUNTRACED);
    }
    else
        wait_pipe(ush, commat, pipedes, buf_exit);
    mx_signal_end(ush, commat, status, buf_exit);
    tcsetpgrp(1, getpid());
}
