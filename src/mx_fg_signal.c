#include "../inc/ush.h"

static void continued_process(t_jobs **list) {
    t_jobs *pl = *list;
    char *number = NULL;

    mx_printerr("[");
    number = mx_itoa(pl->number);
    mx_printerr(number);
    mx_printerr("]  ");
    mx_printerr(&pl->sign);
    mx_printerr(" continued  ");
    for (int i = 0; pl->name[i]; i++) {
        mx_printerr(pl->name[i]);
        mx_printerr(" "); 
    }
    mx_strdel(&number);
    mx_printerr("\n");
}

static void serial_number_sign_setting(t_jobs **list, t_jobs **pl_jobs,
                                                                int lenth) {
    t_jobs *pl_jobs2 = *list;

    while (pl_jobs2) {
        if (pl_jobs2->serial_number > (*pl_jobs)->serial_number)
            pl_jobs2->serial_number = pl_jobs2->serial_number - 1;
        if ((*pl_jobs)->sign != '+') {
            if (pl_jobs2->sign == '+')
                pl_jobs2->sign = '-';
            else if (pl_jobs2->sign == '-')
                pl_jobs2->sign = ' ';
        }
        pl_jobs2 = pl_jobs2->next;
    }
    (*pl_jobs)->sign = '+';
    (*pl_jobs)->serial_number = lenth;
}

static void signal_end(t_ush *ush, t_jobs **pl_jobs, int status, int lenth) {
    if (mx_strcmp((*pl_jobs)->name[0], "ls") != 0) {
        tcsetpgrp(1, getpid());
        continued_process(pl_jobs);
    }
    if (WIFEXITED(status)) {
        ush->exit_code = 0;
        mx_pop_jobs_node(&ush->jobs_list, (*pl_jobs)->number);
    }
    else if (WIFSTOPPED(status)) {
        ush->exit_code = 146;
        mx_cntrl_z_printing((*pl_jobs)->name);
        serial_number_sign_setting(&ush->jobs_list, pl_jobs, lenth);
    }
    else if (WTERMSIG(status) && !(WIFSTOPPED(status))) {
        ush->exit_code = 130;
        mx_pop_jobs_node(&ush->jobs_list, (*pl_jobs)->number);
        mx_printstr("\n");
    }
    else if (status != 0)
        ush->exit_code = 1;
}

void mx_fg_signal(t_ush *ush, t_jobs **pl_jobs, int lenth) {
    int status;
    pid_t wpid;
    t_pid *pl_pid = NULL;

    pl_pid = (*pl_jobs)->pid_list;
    while (pl_pid) {
        kill (-pl_pid->pid, SIGCONT);
        pl_pid = pl_pid->next;
    }
    pl_pid = (*pl_jobs)->pid_list;
    tcsetpgrp(1, pl_pid->pid);
    wpid = waitpid(pl_pid->pid, &status, WUNTRACED);
    signal_end(ush, pl_jobs, status, lenth);
    tcsetpgrp(1, getpid());
}
