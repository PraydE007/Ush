#include "../inc/ush.h"//

void mx_cd_s(char *command, t_ush *ush) {
    struct stat lt;
    char *buf = NULL;

    lstat(command, &lt);
    if ((lt.st_mode & MX_IFMT) == MX_IFDIR) {
        chdir(command);
        free(ush->pwdilda_list->value);
        buf = strdup(ush->pwdilda_list->next->value);
        setenv("OLDPWD", buf, strlen(ush->pwdilda_list->next->value));
        ush->pwdilda_list->value = strdup(ush->pwdilda_list->next->value);
        free(ush->pwdilda_list->next->value);
        setenv("PWD", getcwd(mx_strnew(1024), 1024), 1024);
        ush->pwdilda_list->next->value = strdup(getcwd(mx_strnew(1024), 1024));
    }
    else {
        mx_printerr("cd: not a directory: ");
        mx_printerr(command);
        mx_printerr("\n");
        ush->exit_code = 1;
    }
    free(buf);
}
