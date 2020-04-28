#include "../inc/ush.h"

static void child_recursion(char ***commatrix, int *pipedes, int *pipedes2, int *i) {
        dup2(pipedes[0], 0);
        close(pipedes[0]);
        if (commatrix[(*i) + 1]) {
            close(pipedes2[0]);
            dup2(pipedes2[1], 1);
            close(pipedes2[1]);
        }
        if (execvp(commatrix[(*i)][0], commatrix[(*i)]) == -1)
            mx_error_making(commatrix[(*i)][0]);
        exit(EXIT_FAILURE);
}

static void pipe_creator(char ***commatrix, int *pipedes, int *i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes2[2];

    (*i) = (*i) + 1;
    close(pipedes[1]);
    pipe(pipedes2);
    pid = fork();
    if (pid == 0)
        child_recursion(commatrix, pipedes, pipedes2, i);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        if (commatrix[(*i) + 1])
            pipe_creator(commatrix, pipedes2, i);
        else
            wpid = waitpid(pid, &status, WUNTRACED);
    }
}


void mx_pipe_process_creator(char ***commatrix) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int i = 0;
    int pipedes[2];

    pipe(pipedes);
    pid = fork();
    if (pid == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
        if (execvp(commatrix[i][0], commatrix[i]) == -1)
            mx_error_making(commatrix[i][0]);
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 )
        pipe_creator(commatrix, pipedes, &i);
}
