#include "../inc/ush.h"

void mx_process_creator(t_ush *ush, char **command) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0)
        mx_child_process(ush, command);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0)
        wpid = waitpid(pid, &status, WUNTRACED);
}
