#include "../inc/ush.h"

int mx_exit(t_ush *ush, char **command) {
    int checker = 1;

    mx_printerr("exit\n");
    if (ush->jobs_list) {
        mx_printstr("ush: you have suspended jobs.\n");
        return 999;
    }
    else if (command[0] && !command[1])
        return ush->exit_code;
    else if (command[0] && command[1] && command[2]) {
        mx_printerr("ush: exit: too many arguments\n");
        return ush->exit_code;
    }
    else if (command[0] && command[1]) {
         for (int i = 0; command[1][i]; i++)
            if (!mx_isdigit(command[1][i]))
                checker = 0;
        if (checker == 1)
            return mx_atoi(command[1]);
        else
            return ush->exit_code;
    }
    else
        return ush->exit_code;
}
