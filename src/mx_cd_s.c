#include "../inc/ush.h"//

void mx_cd_s(char *command, t_ush *ush) {
    struct stat lt;

    lstat(command, &lt);
    if ((lt.st_mode & MX_IFMT) == MX_IFDIR) {
        chdir(command);
        free(ush->pwdilda_list->value);
        ush->pwdilda_list->value = strdup(ush->pwdilda_list->next->value);
        free(ush->pwdilda_list->next->value);
        ush->pwdilda_list->next->value = strdup(command);
    }
    else {
        mx_printerr("cd: not a directory: ");
        mx_printerr(command);
        mx_printerr("\n");
        ush->exit_code = 1;
    }
}
