#include "../inc/ush.h"

void err_printer(char *path, t_ush *ush) {
    mx_printerr("cd: no such file or directory: ");
    mx_printerr(path);
    mx_printerr("\n");
    ush->exit_code = 1;
    ush->cd_flags->rip_42 = 1;
}
