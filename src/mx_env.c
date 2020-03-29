#include "../inc/ush.h"
// A LOT OF LINES
static void print_env(char **env) {
    for (int i = 0; env[i]; i++) {
        mx_printstr(env[i]);
        mx_printchar('\n');
    }
}

static bool is_builtin(t_ush *ush, char **command) {
    char **kv = mx_key_value_creation(ush, command[0]);

    if (mx_strcmp("exit", command[0]) == 0) {
        ush->exit_code = mx_exit(command);
        return true;
    }
    else if (mx_strcmp("env", command[0]) == 0) {
        mx_env(ush, command);
        return true;
    }
    else if (mx_strcmp("export", command[0]) == 0) {
        mx_export(ush, command);
        return true;
    }
    else if (mx_strcmp("unset", command[0]) == 0) {
        mx_unset(command, ush);
        return true;
    }
    else if (mx_strcmp("which", command[0]) == 0) {
        mx_which(ush, command);
        return true;
    }
    else if (kv != NULL || ush->equals) {
        if (kv != NULL) {
            mx_adding_variable(ush, command, kv);
            mx_del_strarr(&kv);
        }
        ush->equals = false;
        return true;
    }
    mx_del_strarr(&kv);
    return false;
}

static void env_process_creator(t_ush *ush, char **command, t_list *unset, int i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    extern char **environ;

    pid = fork();
    if (pid == 0) {
        if (ush->flags->i)
            free(environ);
        while (unset) {
            mx_unset(unset->data, ush);
            unset = unset->next;
        }
        if (is_builtin(ush, &command[i]))
            exit(1);
        else if (getenv("PATH")) {
            if (execvp(command[0], command) == -1)
                perror("ush");
            exit(1);
        }
        else {
            if (execv(command[0], command) == -1)
                perror("ush");
            exit(1);
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
    }
}

static char *check_args(char **command) {
    char *res = NULL;

    if (command[0][2])
        res = strdup(&command[0][2]);
    return res;
}

static int flags_trig(t_ush *ush, char **command, t_list *unset) {
    int i = 1;
    int index = 0;

    for (; command[i]; i++) {
        for (int j = 1; command[i][j]; j++) {
            if (command[i][0] == '-') {
                if (command[i][1] == 'P') {
                    if (!command[i + 1] && !command[i][2]) {
                        mx_printerr("env: option requires an argument -- P\n");
                        ush->exit_code = 1;
                        return 0;
                    }
                    int arrlen = mx_strarrlen(&command[i + 1]);
                    char **res = (char **)malloc(sizeof(char *) * (arrlen + 1));
                    printf("\n\n%d\n\n", arrlen);
                    for (int q = i + 1; command[q]; q++) {
                        res[index] = strdup(command[q]);
                        printf("\n%s\n", res[index]);
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
                    if (check_args(&command[i]))
                        mx_push_front(&unset, check_args(&command[i]));
                    else if (command[i + 1])
                        mx_push_front(&unset, command[i + 1]);
                }
            }
        }
    }
    printf("\n\n%s\n\n", unset->data);
    return i;
}

void mx_env(t_ush *ush, char **command) {
    extern char **environ;
    t_list *unset = NULL;

    ush->flags = mx_create_env_flags();
    if (!command[1])
        print_env(environ);
    else {
        int i = flags_trig(ush, command, unset);
        if (i != 0) {
            for (; command[i]; i++) {
                env_process_creator(ush, command, unset, i);
            }
        }
    }
    free(ush->flags);
}