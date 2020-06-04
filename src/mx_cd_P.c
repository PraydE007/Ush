#include "../inc/ush.h"

static void part_for_link(char *command, t_ush *ush)  {
    char *link = mx_strnew(1024);

    readlink(command, link, 1024);
    chdir(command);
    free(ush->pwdilda_list->value);
    ush->pwdilda_list->value = strdup(ush->pwdilda_list->next->value);
    free(ush->pwdilda_list->next->value);
    ush->pwdilda_list->next->value = strdup(command);
    mx_strdel(&link);
    ush->cd_flags->P = 1;
}

void mx_cd_P(char *command, t_ush *ush) {
    struct stat lt;

    lstat(command, &lt);
    if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
        part_for_link(command, ush);
    else {
        chdir(command);
        free(ush->pwdilda_list->value);
        ush->pwdilda_list->value = strdup(ush->pwdilda_list->next->value);
        free(ush->pwdilda_list->next->value);
        ush->pwdilda_list->next->value = strdup(command);
    }
}
