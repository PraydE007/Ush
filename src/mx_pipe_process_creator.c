#include "../inc/ush.h"

static void child_recursion(t_ush *ush, char ***commatrix, int *pipedes, int *pipedes2) {
        dup2(pipedes[0], 0);
        close(pipedes[0]);
        if (commatrix[ush->i + 1]) {
            close(pipedes2[0]);
            dup2(pipedes2[1], 1);
            close(pipedes2[1]);
        }
        mx_child_process(ush, commatrix[ush->i]);
}

static void pipe_creator(t_ush *ush, char ***commatrix, int *pipedes) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes2[2];

    ush->i = ush->i + 1;
    close(pipedes[1]);
    pipe(pipedes2);
    pid = fork();
    if (pid == 0)
        child_recursion(ush, commatrix, pipedes, pipedes2);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        if (commatrix[ush->i + 1])
            pipe_creator(ush, commatrix, pipedes2);
        else
            wpid = waitpid(pid, &status, WUNTRACED);
    }
}

// A LOT OF LINES
void mx_pipe_process_creator(t_ush *ush, char ***commat) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes[2];

    if (commat[1]) {
    pipe(pipedes);
    pid = fork();
    if (pid == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
        mx_child_process(ush, commat[ush->i]);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 )
        pipe_creator(ush, commat, pipedes);
    }
    else
        mx_is_builtin(ush, commat[0]) ? 0 : mx_process_creator(ush, commat[0]);
    ush->i = 0;
}
