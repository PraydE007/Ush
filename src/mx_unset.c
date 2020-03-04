#include "../inc/ush.h"

void mx_unset(char **command, char **env, t_ush *ush) {
    if (command[0] && !command[1])
        mx_printerr("unset: not enough arguments\n");
    else {
        for (int j = 1; command[j]; j++) {
            for (int i = 0; env[i]; i++) {
                char **key = mx_key_value_creation(ush, env[i]);
                if (!mx_strcmp(key[0], command[j])) {
                    unsetenv(key[0]);
                    mx_del_strarr(&key);
                    break;
                }
                mx_del_strarr(&key);
            }
        }
    }
}