#include "../inc/ush.h"
// A LOT OF LINES and COMMENTS
static void print_env(char **env) {
    for (int i = 0; env[i]; i++) {
        mx_printstr(env[i]);
        mx_printchar('\n');
    }
}

static void env_filler(char **env, char **unset, char **environ) {
    int j = 0;
    int flag = 1;
    char **buf = NULL;

    for (int i = 0; environ[i]; i++) {
        for (int y = 0; unset[y]; y++) {
            buf = mx_strsplit(environ[i], '=');
            if (!strcmp(unset[y], buf[0]) && strcmp(buf[0], "_")) {
                flag = 0;
            }
        }
        if (flag == 1) {
            env[j] = strdup(environ[i]);
            j++;
        }
        flag = 1;
    }
}

static void env_process_creator(t_ush *ush, char **command, char **unset, int i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    extern char **environ;
    int env_size = mx_strarrlen(environ);
    char **env = (char **)malloc(sizeof(char *) * env_size + 1);

    env_filler(env, unset, environ);
    pid = fork();
    if (pid != 0) {
        if (ush->flags->i) {
            if (execve(mx_which_str(command[i]), &command[i], NULL) == -1)
                perror("ush");
            exit(1);
        }
        else {
            printf("COMMAND = %s\n", command[i]);
            for (int i = 0; &command[i]; i++)
                printf("WTF? | %s\n", command[i]);
            printf("WHICH_STR = %s\n", mx_which_str(command[i]));
            if (execve(mx_which_str(command[i]), &command[i], env) == -1)
                perror("ush");
            exit(1);
        }
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
    }
    mx_del_strarr(&env);
}

static char *check_args(char **command) {
    char *res = NULL;

    if (command[0][2])
        res = strdup(&command[0][2]);
    return res;
}

static int flags_trig(t_ush *ush, char **command, char **unset) {
    int i = 1;
    int index = 0;
    int u = 0;

    for (; command[i]; i++) {
        for (int j = 1; command[i][j]; j++) {
            if (command[i][0] == '-') {
                if (command[i][1] == 'P') {
                    if (!command[i + 1] && !command[i][2]) {
                        mx_printerr("env: option requires an argument -- P\n");
                        ush->exit_code = 1;
                        return 0;
                    }
                    int arrlen = mx_strarrlen(&command[i]);
                    char **res = (char **)malloc(sizeof(char *) * (arrlen + 1));
                    for (int q = i + 1; command[q]; q++) {
                        res[index] = strdup(command[q]);
                        index++;
                    }
                    res[arrlen] = NULL;
                    ush->flags->P = 1;
                    env_process_creator(ush, res, unset, i);
                    return 0;
                }
                else if (command[i][1] == 'i')
                    ush->flags->i = 1;
                else if (command[i][1] == 'u') {
                    ush->flags->u = 1;
                    if (check_args(&command[i])) {
                        unset[u] = strdup(check_args(&command[i]));
                        u++;
                    }
                    else if (command[i + 1]) {
                        unset[u] = strdup(command[i + 1]);
                        u++;
                    }
                }
            }
        }
    }
    return i;
}

void mx_env(t_ush *ush, char **command) {
    extern char **environ;
    char **unset = (char **)malloc(sizeof(char *) * mx_strarrlen(command));
    for (int i = 0; mx_strarrlen(command) >= i; i++)
        unset[i] = NULL;

    unset[0] = NULL;
    ush->flags = mx_create_env_flags();
    if (!command[1])
        print_env(environ);
    else {
        int i = flags_trig(ush, command, unset);
        if (i != 0) {
            //for (; command[i]; i++) {
                env_process_creator(ush, command, unset, i - 1);
            //}
        }
    }
    free(ush->flags);
}
