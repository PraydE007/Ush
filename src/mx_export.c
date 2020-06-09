#include "../inc/ush.h"

static void export_error(t_ush *ush, char *str) {
    if (ush->trigger) {
        ush->trigger = false;
        mx_printerr("ush: not an identifier: ");
        mx_printerr(str);
        mx_printerr("\n");
    }
    else if (!ush->equals) {
        mx_printerr("ush: not valid in this context: ");
        mx_printerr(str);
        mx_printerr("\n");
    }
    ush->exit_code = 1;
}

static void export_condition(t_ush *ush, char **kv) {
    if (mx_check_key_allow(ush, kv[0])) {
        mx_isvariable(ush, kv);
        if (!ush->trigger) {
            if (mx_strarrlen(kv) > 1) 
                setenv(kv[0], kv[1], 1);
            else
                setenv(kv[0], "", 1);
        }
        ush->trigger = false;
    }
    else
        export_error(ush, kv[0]);
}

static void  variable_error_cleaningg(t_ush *ush, char **command, int *i) {
    char **kv = NULL;

    if (ush->equals) {
        for (; (*i) > 0; (*i)--) {
            kv = mx_key_value_creation(ush, command[(*i)]);
            if (kv != NULL) {
                unsetenv(kv[0]);
                mx_del_strarr(&kv);
            }
        }
        ush->equals = false;
    }
}

static void  export_making(t_ush *ush, char **command) {
    char **kv = NULL;
    int i = 1;

    for (; command[i]; i++) {
        kv = mx_key_value_creation(ush, command[i]);
        if (kv != NULL) {
            export_condition(ush, kv);
            mx_del_strarr(&kv);
        }
        else if (mx_check_key_allow(ush, command[i]))
            mx_env_variable_checking(&ush->variable_list, command[i]);
        else
            export_error(ush, command[i]);
    }
    i--;
    variable_error_cleaningg(ush, command, &i);
}

void  mx_export(t_ush *ush, char **command) {
    char **export = NULL;
    int lenth = mx_strarrlen(command);
    extern char **environ;

    if (lenth == 1) {
        export = mx_export_matrix_creator(environ);
        for (int i = 0; export[i]; i++)
            printf("%s\n", export[i]);
        mx_del_strarr(&export);
    }
    else 
        export_making(ush, command);
    ush->exit_code = 0;
}
