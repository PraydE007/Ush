#include "../inc/ush.h"

static void print_env(char **env) {
    for (int i = 0; env[i]; i++) {
        mx_printstr(env[i]);
        mx_printchar('\n');
    }
}

static bool is_builtin(t_ush *ush, char **command, char **env) {
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
        mx_export(ush, command, env);
        return true;
    }
    else if (mx_strcmp("unset", command[0]) == 0) {
        mx_unset(command, env, ush);
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

static void env_process_creator(t_ush *ush, char **command, char **env, int i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0) {
        unsetenv("PATH");
        if (mx_is_built_in(command[1]))
            is_builtin(ush, &command[i], env);
        else if (getenv("PATH") != 0) {
            if (execvp(command[1], &command[i]) == -1)
                perror("ush");
            exit(1);
        }
        else {
            if (execv(command[1], &command[i]) == -1)
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

static char *check_args(char **command, char **unset) {
    char *res = NULL;

    if (command[0][2]) {
        res = strdup(&command[0][2]);
    }
    return res;
}

//static int flags_trig(char **command, char **unset) {
//    for (int i = 1; command[i][j]; i++) {
//        for (int j = 0; command[i][j]; j++) {
//            if (command[i][0] == '-') {
//                if (command[i][j] == 'P') {
//
//                    return i;
//                }
//                else if (command[i][j] == 'i')
//
//                else if (command[i][j] == 'u')
//
//            }
//        }
//    }
//}

void mx_env(t_ush *ush, char **command) {
    extern char **environ;
    char **unset = NULL;

    if (!command[1])
        print_env(environ);
    else {
//        int i = flags_trig(command, unset);
        int i = 1;
        char *res = check_args(&command[1], unset);
        printf("\n\n%s\n\n", res);
        for (; command[i]; i++) {
            env_process_creator(ush, command, environ, i);
        }
    }
}