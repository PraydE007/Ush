#include "../inc/ush.h"

static void cd_minus(t_ush *ush) {
    chdir(ush->pwdilda_list->value);
    free(ush->pwdilda_list->value);
    setenv("OLDPWD", strdup(ush->pwdilda_list->next->value),
            strlen(ush->pwdilda_list->next->value));
    ush->pwdilda_list->value = strdup(ush->pwdilda_list->next->value);
    free(ush->pwdilda_list->next->value);
    setenv("PWD", getcwd(mx_strnew(1024), 1024), 1024);
    ush->pwdilda_list->next->value = strdup(getcwd(mx_strnew(1024), 1024));
    mx_printstr(ush->pwdilda_list->next->value);
    mx_printchar(10);
}

static void err_printer(char *path, t_ush *ush) {
    mx_printerr("cd: no such file or directory: ");
    mx_printerr(path);
    mx_printerr("\n");
    ush->exit_code = 1;
    ush->cd_flags->rip_42 = 1;
}

static char *getpath_cd(char **command, t_ush *ush, int i) {
    struct stat lt;
    char *path;

    if (!command[i] && getenv("HOME"))
        path = getenv("HOME");
    else
        path = command[i];
    if (command[i] && command[i + 1] && command[i + 2]) {
        mx_printerr("cd: too many arguments\n");
        ush->exit_code = 1;
        ush->cd_flags->rip_42 = 1;
    }
    if (lstat(path, &lt) < 0 && !ush->cd_flags->rip_42)
        err_printer(path, ush);
    if (command[i] && command[i + 1]
        && !command[i + 2] && !ush->cd_flags->rip_42) {
        printf("%s\n", ush->pwdilda_list->next->value);
        ush->cd_flags->rip_42 = 1;
    }
    return path;
}

static void changedir(char *path, t_ush *ush) {
    chdir(path);
    free(ush->pwdilda_list->value);
    setenv("OLDPWD", strdup(ush->pwdilda_list->next->value),
            strlen(ush->pwdilda_list->next->value));
    ush->pwdilda_list->value = strdup(ush->pwdilda_list->next->value);
    free(ush->pwdilda_list->next->value);
    setenv("PWD", getcwd(mx_strnew(1024), 1024), 1024);
    ush->pwdilda_list->next->value = strdup(getcwd(mx_strnew(1024), 1024));
}

void mx_cd(char **command, t_ush *ush) {
    int i;
    ush->cd_flags = (t_cd_info *)malloc(sizeof(t_cd_info));
    char *path;

    memset(ush->cd_flags, 0, sizeof(t_cd_info));
    ush->cd_flags->P = 0;
    i = mx_parser_cd(command, ush);
    path = getpath_cd(command, ush, i);
    if (!ush->cd_flags->rip_42) {
        if (ush->cd_flags->minus)
            cd_minus(ush);
        else if (ush->cd_flags->s)
            mx_cd_s(path, ush);
        else if (ush->cd_flags->P)
            mx_cd_P(path, ush);
        else
            changedir(path, ush);
    }
    free(ush->cd_flags);
}
