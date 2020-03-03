#include "../inc/ush.h"

// static bool have_equals(char *env) {
//     int i = 0;

//     while (env[i]) {
//         if (env[i + 2]) {
//             if (env[i] == '=' && env[i + 1] == '=') {
//                 mx_printerr("ush: ");
//                 mx_printerr(&env[i + 2]);
//                 mx_printerr(" not found\n");
//                 return false;
//             }
//         }
//         if (env[i] == '=')
//             return true;
//         i++;
//     }
//     return false;
// }

static bool check_key_allow(char **kv) {
    int i = 0;

    while (kv[0][i]) {
        if ((kv[0][i] < 48 || (kv[0][i] > 57 && kv[0][i] < 65)
            || (kv[0][i] > 90 && kv[0][i] < 97) || kv[0][i] > 122)
            && (kv[0][i] != 36 && kv[0][i] != 95)) {
            return false;
        }
        i++;
    }
    return true;
}

static char **key_value_creation(char *env) {
    char **kv = NULL;

    if (mx_have_equals(env)) {
        kv = mx_strsplit(env, '=');
    }
    return kv;
}

static void export_error(char *str) {
    mx_printerr("ush: not valid in this context:");
    mx_printerr(str);
    mx_printerr("\n");
}

static void  export_making(char **command, char **env) {
    char **kv = NULL;

    for (int i = 1; command[i]; i++) {
        kv = key_value_creation(command[i]);
        if (kv != NULL) {
            if (mx_strarrlen(kv) > 1 && check_key_allow(kv))
                setenv(kv[0], kv[1], 1);
            else if (check_key_allow(kv))
                setenv(kv[0], "", 1);
            else
                export_error(kv[0]);
            mx_del_strarr(&kv);
        }
    }
}

void  mx_export(char **command, char **env) {
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
        export_making(command, env);
}
