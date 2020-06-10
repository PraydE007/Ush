#include "../inc/ush.h"

static void print_env(char **env) {
    for (int i = 0; env[i]; i++) {
        mx_printstr(env[i]);
        mx_printchar('\n');
    }
}

void mx_env(t_ush *ush, char **command) {
    extern char **environ;
    int len = mx_strarrlen(command) + 1;
    char **unset = (char **)malloc(sizeof(char *) * len);

    for (int i = 0; i < len; i++)
        unset[i] = NULL;
    ush->flags = mx_create_env_flags();
    if (!command[1])
        print_env(environ);
    else {
        int i = mx_parser_env(ush, command, unset);
        if (i != 0 && !ush->flags->end)
            env_process_creator(ush, command, unset, i - 1);
    }
    free(ush->flags);
    mx_del_strarr(&unset);
}
