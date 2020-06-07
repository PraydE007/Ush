#include "../inc/ush.h"

// static void cntrl_z_printing(char **command) {
//     mx_printstr("\nush: suspended  ");
//     for (int i = 0; command[i]; i++) {
//         mx_printstr(command[i]);
//         if (command[i + 1])
//             mx_printstr(" ");
//     }
//     mx_printstr("\n");
// }

static void cntrl_z_condition(t_ush *ush, char **command) {
    t_pid *pid = NULL;

    ush->exit_code = 146;
    mx_push_back_pid(&pid, ush->pid2);
    mx_push_jobs_node(&ush->jobs_list, &pid, command, NULL);
    mx_cntrl_z_printing(command);
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
    else if (WIFSTOPPED(status))
        cntrl_z_condition(ush, command);
    else if (WTERMSIG(status)) {
        ush->exit_code = 130;
        mx_printstr("\n");
    }
    else if (status != 0)
        ush->exit_code = 1;
}

void mx_process_creator(t_ush *ush, char **command) {
    pid_t wpid = 0;
    int status = 0;

    ush->pid2 = fork();
    if (ush->pid2 == 0)
        mx_child_process(ush, command);
    else if (ush->pid2 < 0)
        perror("ush");
    else if (ush->pid2 > 0) {
        setpgid(ush->pid2, ush->pid2);
        tcsetpgrp(1, ush->pid2);
        wpid = waitpid(ush->pid2, &status, WUNTRACED);
        signal_end(ush, command, status);
        tcsetpgrp(1, getpid());
    } 
}
Z