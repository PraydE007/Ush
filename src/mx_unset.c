#include "../inc/ush.h"

static void variable_out(char *command, t_variable *list) {
    t_variable *buf = list;
    int index = 0;

    while (buf) {
        if (!mx_strcmp(command, buf->key)) {
            mx_pop_specific(&list, index);
            return;
        }
        buf = buf->next;
        index++;
    }
}

void mx_unset(char **command, char **env, t_ush *ush) {
    if (command[0] && !command[1])
        mx_printerr("unset: not enough arguments\n");
    else {
        for (int j = 1; command[j]; j++) {
            variable_out(command[j], ush->variable_list);
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