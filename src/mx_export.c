#include "../inc/ush.h"

static void export_error(char *str) {
    mx_printerr("ush: not valid in this context: ");
    mx_printerr(str);
    mx_printerr("\n");
}

static void  export_making(t_ush *ush, char **command, char **env) {
    char **kv = NULL;

    for (int i = 1; command[i]; i++) {
        kv = mx_key_value_creation(ush, command[i]);
        if (kv != NULL) {
            if (mx_strarrlen(kv) > 1 && mx_check_key_allow(kv)) {
                mx_isvariable(&ush->variable_list, kv);// setenv(kv[0], kv[1], 1);
            }
            else if (mx_check_key_allow(kv)) {
                mx_isvariable(&ush->variable_list, kv);// setenv(kv[0], "", 1);
            }
            else
                export_error(kv[0]);
            mx_del_strarr(&kv);
        }
        else
            mx_env_variable_checking(&ush->variable_list, command[i]);
    }
}

void  mx_export(t_ush *ush, char **command, char **env) {
    char **export = NULL;
    char **kv = NULL;
    int lenth = mx_strarrlen(command);

    if (lenth == 1) {
        export = mx_export_matrix_creator(env);
        for (int i = 0; export[i]; i++)
            printf("%s\n", export[i]);
        mx_del_strarr(&export);
    }
    else 
        export_making(ush, command, env);
}
