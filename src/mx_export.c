#include "ush.h"

static bool have_equals(char *env) {
    int i = 0;
    // printf("11111\n");

    while (env[i]) {
        if (env[i + 2]) {
            if (env[i] == '=' && env[i + 1] == '=') {
                mx_printerr("ush: ");
                mx_printerr(&env[i + 2]);
                mx_printerr(" not found\n");
                return false;
            }
        }
        if (env[i] == '=')
            return true;
        i++;
    }
    return false;
}

static char **key_value_creation(char *env) {
    char **kv = NULL;

    if (have_equals(env)) {
        kv = mx_strsplit(env, '=');
    }
    return kv;
}

void  mx_export(char **command, char **env) {
    // t_export *pex = *export_list;
    // t_t_node *pc = *command;
    char **kv = NULL;
    int lenth = mx_strarrlen(command);
                // setenv("DDDD", "", 1);
                // printf("env2222: \n");
                // int i = 0;
                // while (env[i]) {
                //     printf("%s\n", env[i]);
                //     i++;
                // }
    if (lenth == 1) {
        for (int i = 0; env[i]; i++)
            printf("%s\n", env[i]);
        // while (pex) {
        //     mx_printstr(pex->key);
        //     mx_printstr("=");
        //     if (pex->value)
        //         mx_printstr(pex->value);
        //     else
        //         mx_printstr("''");
        //     mx_printstr("\n");
        //     pex = pex->next;
        // }
    }
    else {
        for (int i = 1; command[i]; i++) {
            kv = key_value_creation(command[i]);
            // printf("22222\n");
            if (kv != NULL) {
                if (mx_strarrlen(kv) > 1) {
                    setenv(kv[0], kv[1], 1);
                }
                else
                    setenv(kv[0], "", 1);
            }
            // perror("ush");
            mx_del_strarr(&kv);
        }
    }
    // printf("33333\n");
}
