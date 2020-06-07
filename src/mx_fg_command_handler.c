#include "../inc/ush.h"

static void fg_error(t_ush *ush, t_jobs **pl_jobs, char *command) {

    if (command[0] == '%' && mx_atoi(&command[1]) > 0) {
        mx_printerr("fg: ");
        mx_printerr(command);
        mx_printerr(": no such job\n");
    }
    else {
        *pl_jobs = NULL;
        mx_printerr("fg: job not found: ");
        if (command[0] == '%')
            mx_printerr(&command[1]);
        else
            mx_printerr(command);
        mx_printerr("\n");
    }
    ush->triger++;
}

static void first_char_percent(t_ush *ush, t_jobs **pl_jobs, char *command,
                                                                int lenth) {
    if (mx_atoi(&command[1]) > 0) {
        while (*pl_jobs) {
            if ((*pl_jobs)->number == mx_atoi(&command[1]))
                return;
            *pl_jobs = (*pl_jobs)->next;
        }
    }
    else {
        for (; lenth > 0; lenth--) {
            while (*pl_jobs) {
                if ((*pl_jobs)->serial_number == lenth
                    && mx_strcmp((*pl_jobs)->name[0], &command[1]) == 0)
                    return;
                *pl_jobs = (*pl_jobs)->next;
            }
            *pl_jobs = ush->jobs_list;
        }
    }
    fg_error(ush, pl_jobs, command);
}

static void without_percent(t_ush *ush, t_jobs **pl_jobs, char *command,
                                                                int lenth) {
    for (; lenth > 0; lenth--) {
        while (*pl_jobs) {
            if ((*pl_jobs)->serial_number == lenth
                && mx_strcmp((*pl_jobs)->name[0], command) == 0)
                return;
            *pl_jobs = (*pl_jobs)->next;
        }
        *pl_jobs = ush->jobs_list;
    }
    fg_error(ush, pl_jobs, command);
}

static void percent_fg(t_jobs **pl_jobs) {

    while (*pl_jobs) {
        if ((*pl_jobs)->sign == '+')
            break;
        *pl_jobs = (*pl_jobs)->next;
    }
}

void mx_fg_command_handler(t_ush *ush, t_jobs **pl_jobs, char **command,
                                                                int lenth) {
    int size = mx_strarrlen(command);

    for (int i = 1; i < size; i++) {
        if (ush->triger > 0)
            break;
        while (mx_strcmp(command[i], "\0") == 0)
            i++;
        if (i < size) {
            *pl_jobs = ush->jobs_list;
            if (mx_strcmp(command[i], "%") == 0
                || (command[i][0] == '%' && command[i][1] == '%'))
                percent_fg(pl_jobs);
            else if (command[i][0] == '%')
                first_char_percent(ush, pl_jobs, command[i], lenth);
            else
                without_percent(ush, pl_jobs, command[i], lenth);
            (*pl_jobs) ? mx_fg_signal(ush, pl_jobs, lenth) : (void)0;
        }
    }
    ush->triger = 0;
}
