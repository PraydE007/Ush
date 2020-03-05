#include "../inc/ush.h"

int mx_exit(char **command) {
    int checker = 1;

    mx_printerr("exit\n");
    if (command[0] && !command[1])
        return 1;
    else if (command[0] && command[1] && command[2]) {
        mx_printerr("ush: exit: too many arguments\n");
        return 1;
    }
    else if (command[0] && command[1]) {
         for (int i = 0; command[1][i]; i++)
            if (!mx_isdigit(command[1][i]))
                checker = 0;
        if (checker == 1)
            return mx_atoi(command[1]);
        else
            return 1;
    }
    else
        return 1;
}
