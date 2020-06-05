 #include "../inc/ush.h"

static void percent_fg(t_ush *ush, t_jobs **pl_jobs, char **command) {
    int lenth = mx_jobs_list_len(&ush->jobs_list);

    *pl_jobs = ush->jobs_list;
    if (command[1][0] == '%') {
        if (mx_atoi(&command[1][1]) > 0) {
            while (*pl_jobs) {
                if ((*pl_jobs)->number == mx_atoi(&command[1][1]))
                    return;
                *pl_jobs = (*pl_jobs)->next;
            }
        }
        else {
            for (; lenth > 0; lenth--) {
                while (*pl_jobs) {
                    if ((*pl_jobs)->number == lenth
                        && mx_strcmp((*pl_jobs)->name[0], &command[1][1]) == 0)
                        return;
                    *pl_jobs = (*pl_jobs)->next;
                }
                *pl_jobs = ush->jobs_list;
            }
        }
    }
    else {
        for (; lenth > 0; lenth--) {
            while (*pl_jobs) {
                if ((*pl_jobs)->number == lenth && mx_strcmp((*pl_jobs)->name[0], command[1]) == 0)
                    return;
                *pl_jobs = (*pl_jobs)->next;
            }
            *pl_jobs = ush->jobs_list;
        }
    }
    mx_printstr("fg: ");
    mx_printstr(command[1]);
    mx_printstr(" no such job\n");
}

void mx_fg(t_ush *ush, char **command) {
    int status;
    pid_t wpid;
    t_jobs *pl_jobs = ush->jobs_list;
    t_pid *pl_pid = NULL;

    if (pl_jobs == NULL) {
        mx_printstr("fg: no current job\n");
        ush->exit_code = 1;
        return;
    }
    else if (mx_strarrlen(command) == 1) {
        while (pl_jobs) {
            if (pl_jobs->sign == '+')
                break;
            pl_jobs = pl_jobs->next;
        }
    }
    else if (mx_strarrlen(command) > 1) {
        percent_fg(ush, &pl_jobs, command);
        // if (command[1][0] == '%') {
        //     if (mx_atoi(&command[1][1]) > 0) {
        //         while (pl_jobs) {
        //             if (pl_jobs->number == mx_atoi(&command[1][1]))
        //                 break;
        //             pl_jobs = pl_jobs->next;
        //         }
        //     }
        //     else {
        //         mx_printstr("fg: ");
        //         mx_printstr(command[1]);
        //         mx_printstr(" no such job\n");
        //     }
            
        // }
    }
// printf("sign: %c\n", pl_jobs->sign);
    pl_pid = pl_jobs->pid_list;
    while (pl_pid) {
        kill (pl_pid->pid, SIGCONT);
        pl_pid = pl_pid->next;
    }
    pl_pid = pl_jobs->pid_list;
    tcsetpgrp(1, pl_pid->pid);
    wpid = waitpid(pl_pid->pid, &status, WUNTRACED);
    tcsetpgrp(1, getpid());
    if (WIFEXITED(status))
        ush->exit_code = 0;
    else if (WIFSTOPPED(status)) {
        ush->exit_code = 146;
        mx_cntrl_z_printing(pl_jobs->name);
    }
    else if (WTERMSIG(status) && !(WIFSTOPPED(status))) {
        ush->exit_code = 130;
        mx_pop_jobs_node(&ush->jobs_list, pl_jobs->number);
        mx_printstr("\n");
    }
    else if (status != 0)
        ush->exit_code = 1;
}
