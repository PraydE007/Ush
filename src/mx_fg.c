 #include "../inc/ush.h"

void mx_fg(t_ush *ush, char **command) {
    int status;
    pid_t wpid;
    t_jobs *pl_jobs = ush->jobs_list;
    t_pid *pl_pid = NULL;

    command = command + 1 - 1; // workaround for unused war

if (pl_jobs == NULL) {
    mx_printstr("fg: no current job\n");
    ush->exit_code = 1;
    return;
}
printf("sign: %c\n", pl_jobs->sign);
    while (pl_jobs) {
        if (pl_jobs->sign == '+')
            break;
        pl_jobs = pl_jobs->next;
    }
    pl_pid = pl_jobs->pid_list;
    while (pl_pid) {
        kill (pl_pid->pid, SIGCONT);
        pl_pid = pl_pid->next;
    }
    pl_pid = pl_jobs->pid_list;
    
    tcsetpgrp(1, pl_pid->pid);
    wpid = waitpid(pl_pid->pid, &status, WUNTRACED);
    tcsetpgrp(1, getpid());
    if (WIFEXITED(status)) {
        ush->exit_code = 0;
    //     pid_buf = (*pid_ar)->next;
    //     free((*pid_ar)->name);
    //     free((*pid_ar));
    //     (*pid_ar) = pid_buf;
    }
    else if (WIFSTOPPED(status)) {
        ush->exit_code = 146;
        mx_cntrl_z_printing(pl_jobs->name);
    }
    else if (WTERMSIG(status) && !(WIFSTOPPED(status))) {
        ush->exit_code = 130;
        mx_pop_jobs_node(&ush->jobs_list, pl_jobs->number);
        mx_printstr("\n");
        // free((*pid_ar)->name);
        // pid_buf = (*pid_ar)->next;
        // free((*pid_ar));
        // (*pid_ar) = pid_buf;
    }
    else if (status != 0)
        ush->exit_code = 1;
}
