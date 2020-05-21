#include "../inc/ush.h"

static void cntrl_z_printing(char **command) {
    mx_printstr("\nush: suspended  ");
    for (int i = 0; command[i]; i++) {
        mx_printstr(command[i]);
        if (command[i + 1])
            mx_printstr(" ");
    }
    mx_printstr("\n");
}

static void signal_end(t_ush *ush, char **command, int status) {
    if (WIFEXITED(status)) {
        if (status == 256)
            ush->exit_code = 1;
        else if (WEXITSTATUS(status))
            ush->exit_code = 127;
        else
            ush->exit_code = 0;
    }
    else if (WIFSTOPPED(status)) {
        ush->exit_code = 146;
        cntrl_z_printing(command);
    }
    else if (WTERMSIG(status)) {
        ush->exit_code = 130;
        mx_printstr("\n");
    }
    else if (status != 0)
        ush->exit_code = 1;
}

void mx_process_creator(t_ush *ush, char **command) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0)
        mx_child_process(ush, command);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        setpgid(pid, pid);
        tcsetpgrp(1, pid);
        wpid = waitpid(pid, &status, WUNTRACED);
        signal_end(ush, command, status);
        tcsetpgrp(1, getpid());
    } 
}
