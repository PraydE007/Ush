#include "../inc/ush.h"

static void main_part(char *command, t_ush *ush, bool *flags) {
    for (int j = 1; command[j]; j++) {
        if (command[j] == 'P')
            flags[MX_P] = 1;
        else if (command[j] == 'L') {
            if (!flags[MX_P])
                flags[MX_L] = 1;
        }
        else {
            mx_printerr("pwd: bad option: ");
            mx_printchar(command[j]);
            mx_printerr("\n");
            ush->exit_code = 1;
            flags[MX_END] = 1;
            break;
        }
    }
}

void parser(char **command, t_ush *ush, bool *flags) {
    for (int i = 1; command[i] && !flags[2]; i++) {
        if (command[i][0] == '-')
            main_part(command[i], ush, flags);
        else {
            mx_printerr("pwd: too many arguments\n");
            ush->exit_code = 1;
            flags[MX_END] = 1;
            break;
        }
    }
    if (flags[MX_P])
        flags[MX_L] = 0;
}

static void print_pwd(bool *flags) {
    char *cwd = mx_strnew(1024);

    getcwd(cwd, 1024);
    if (getenv("PWD")) {
        if (flags[MX_P])
            mx_printstr(cwd);
        else
            mx_printstr(getenv("PWD"));
    }
    else
        mx_printstr(cwd);
    mx_printchar('\n');
    free(cwd);
}

void mx_pwd(char **command, t_ush *ush) {
    bool *pwd_flags = (bool *)malloc(sizeof(bool) * 3);

    memset(pwd_flags, 0, sizeof(bool) * 3);
    parser(command, ush, pwd_flags);
    if (!pwd_flags[MX_END])
        print_pwd(pwd_flags);
    free(pwd_flags);
}
