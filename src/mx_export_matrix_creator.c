#include "../inc/ush.h"

void mx_sort_export(char **env) {
    for (int i = 0; env[i + 1]; i++) {
        if (mx_strcmp_export(env[i], env[i + 1]) > 0) {
            mx_swap_str(&env[i], &env[i + 1]);
            for (int j = i; j > 0; j--) {
                if (mx_strcmp_export(env[j], env[j - 1]) < 0)
                    mx_swap_str(&env[j], &env[j - 1]);
                else
                    break;
            }
        }
    }
}

char **mx_export_matrix_creator(char **env) {
    int size = mx_strarrlen(env);
    char **copy = NULL;

    copy = (char **)malloc(sizeof(char *) * (size + 1));
    for (int i = 0; i <= size; i++)
        copy[i] = NULL;
    for (int i = 0; env[i]; i++) {
        copy[i] = mx_strdup(env[i]);
        // printf("copy:   ");
        // printf("%s,\n", copy[i]);
        // printf("env:   ");
        // printf("%s,\n", env[i]);
    }
    // if (copy)
    //     mx_sort_export(copy);
    return copy;
}
