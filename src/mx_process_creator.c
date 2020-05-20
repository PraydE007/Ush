#include "../inc/ush.h"

static void signal_end(char **command, int status) {
    // if (WIFEXITED(status))
    //     error_number = 0;
    // else 
    if (WIFSTOPPED(status)) {
        // error_number = 146;
        mx_printstr("\nush: suspended  ");
        for (int i = 0; command[i]; i++) {
            mx_printstr(command[i]);
            if (command[i + 1])
                mx_printstr(" ");
        }
        mx_printstr("\n");
    }
    else if (WTERMSIG(status)) {
        // error_number = 130;
        mx_printstr("\n");
    }
        // else if (status != 0)
        //    error_number = 1;

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
        signal_end(command, status);
        tcsetpgrp(1, getpid());
    } 
}
