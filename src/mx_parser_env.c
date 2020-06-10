#include "../inc/ush.h"

static char *check_args(char **command) {
    char *res = NULL;

    if (command[0][2])
        res = strdup(&command[0][2]);
    return res;
}

static void flag_P(char **command, int i, t_ush *ush, char **unset) {
    int index = 0;
    int arrlen = mx_strarrlen(&command[i]);
    char **res = (char **)malloc(sizeof(char *) * (arrlen + 1));

    res[arrlen] = NULL;
    if (!command[i] && !command[i][2]) {
        mx_printerr("env: option requires an argument -- P\n");
        ush->exit_code = 1;
    }
    for (int q = i; command[q]; q++) {
        res[index] = strdup(command[q]);
        index++;
    }
    ush->flags->P = 1;
    env_process_creator(ush, res, unset, i);
    ush->flags->end = 1;
    mx_del_strarr(&res);
}

static bool zatichka_v_lob(char **unset, char **command, int i, int *u) {
    if (check_args(&command[i])) {
        unset[*u] = strdup(check_args(&command[i]));
        (*u)++;
        return true;
    }
    else if (command[i + 1]) {
        unset[*u] = strdup(command[i + 1]);
        (*u)++;
        return true;
    }
    return false;
}

int mx_parser_env(t_ush *ush, char **command, char **unset) {
    int i = 1;
    int u = 0;

    for (; command[i]; i++) {
        for (int j = 1; command[i][j]; j++) {
            if (command[i][0] == '-') {
                if (command[i][1] == 'P' && command[i + 1])
                    flag_P(command, i + 1, ush, unset);
                else if (command[i][1] == 'i')
                    ush->flags->i = 1;
                else if (command[i][1] == 'u') {
                    ush->flags->u = 1;
                    if (zatichka_v_lob(unset, command, i, &u))
                        break;
                }
            }
        }
    }
    return i;
}
