#include "../inc/ush.h"

static int counter_add_env(char **command) {
    int res = 0;
    int trig = 0;

    if (command && *command) {
        for (int i = 0; command[i]; i++) {
            for (int j = 0; command[i][j]; j++) {
                if (command[i][j] == '=')
                    trig++;
            }
            if (trig == 0)
                return i;
            if (trig > 0)
                res++;
            res = 0;
            trig = 0;
        }
    }
    return res;
}

static int check_for_P(char *path, char *exe) {
    char *command = mx_strjoin(path, exe);
    printf("CHECK_P = %s\n", command);
    int res = 0;
    struct stat lt;

    lstat(exe, &lt);
    if ((lt.st_mode & MX_IXUSR) == MX_IXUSR) {
        free(command);
        return 2;
    }
    lstat(command, &lt);
    if ((lt.st_mode & MX_IXUSR) == MX_IXUSR)
        res = 1;
    free(command);
    return res;
}

static void print_env(char **env) {
    for (int i = 0; env[i]; i++) {
        mx_printstr(env[i]);
        mx_printchar('\n');
    }
}

static void env_filler(char **env, char **unset, char **add_env, char **environ) {
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
    if (add_env[0]) {
        for (int i = 0; add_env[i]; i++) {
            env[j] = strdup(add_env[i]);
            j++;
        }
    }
}

static void env_process_creator(t_ush *ush, char **command, char **unset, char **add_env) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    extern char **environ;
    int env_size = mx_strarrlen(environ);
    char **env = (char **)malloc(sizeof(char *) * env_size + 1 + counter_add_env(command));

    env[env_size + 1] = NULL;
    env_filler(env, unset, add_env, environ);
//    for (int i = 0; env[i]; i++)
//        printf("ENV = %s\n", env[i]);
    pid = fork();
    if (pid == 0) {
        if (ush->flags->P) {
            if (check_for_P(command[0], command[1])) {
                if (execve(command[1], &command[1], env) == -1)
                    perror("ush");
                exit(1);
            }
            if (!check_for_P(command[0], command[1])) {
                mx_printerr("env: ");
                mx_printerr(command[1]);
                mx_printerr(": No such file or directory\n");
            }
            else if (ush->flags->i) {
                if (execve(mx_strjoin(command[0], command[1]), &command[1], NULL) == -1)
                    perror("ush");
                exit(1);
            }
            else {
                if (execve(mx_strjoin(command[0], command[1]), &command[1], env) == -1)
                    perror("ush");
                exit(1);
            }
        }
        else if (ush->flags->i) {
            if (execve(mx_which_str(command[0]), &command[0], NULL) == -1)
                perror("ush");
            exit(1);
        }
        else {
            for (int i = 0; command[i]; i++)
                printf("COMMAND = %s\n", command[i]);
            printf("WHICH_STR = %s\n", mx_which_str(command[0]));
            if (check_for_P(NULL, command[0]) == 2) {
                if (execve(command[0], command, env) == -1)
                    perror("ush");
                exit(1);
            }
            if (execve(mx_which_str(command[0]), command, env) == -1)
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
//    mx_del_strarr(&env);
}

static char *check_args(char **command) {
    char *res = NULL;

    if (command[0][2])
        res = strdup(&command[0][2]);
    return res;
}

static char **prepare_command(char **command, int i) {
    int index = 0;
    int arrlen = mx_strarrlen(&command[i]);
    char **res = (char **)malloc(sizeof(char *) * (arrlen + 1));

    for (int i = 0; res[i]; i++)
        res[i] = NULL;
    if (command[i][2])
        command[i] = check_args(&command[i]);
    for (int q = i + 1; command[q]; q++) {
        res[index] = strdup(command[q]);
        index++;
    }
    res[arrlen] = NULL;
    return res;
}

static char **flags_trig(t_ush *ush, char **command, char **unset, char **add_env) {
    int i = 1;
    int u = 0;
    int flag_env = 0;
    char **new_command = NULL;

    for (int z = 0; command[z]; z++)
        printf("FLAG COMMAND = %s\n", command[z]);
    for (; command[i]; i++) {
        if (command[i][0] == '-') {
            for (int a = 1; command[i][a]; a++)
                if (command[i][a] == '=')
                    perror("env");
        }
        for (int j = 1; command[i][j]; j++) {
            if (command[1][0] != '-') {
                if (command[i][1] == 'P') {
                    if (!command[i + 1] && !command[i][2]) {
                        mx_printerr("env: option requires an argument -- P\n");
                        ush->exit_code = 1;
                        return 0;
                    }
                    new_command = prepare_command(command, i);
                    ush->flags->P = 1;
                    env_process_creator(ush, new_command, unset, add_env);
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
    if (command[i]) {
        if (command[i][0]) {
            for (int a = 0; command[i][a]; a++)
                if (command[i][a] == '=')
                    flag_env = 1;
        }
    }
    if (flag_env) {
        int counter = counter_add_env(&command[i]);
        for (int a = i; counter; a++) {
            add_env[a] = command[a];
            counter--;
        }
        i += counter;
    }
    printf("FLAG I = %d\n", i);
    return new_command;
}

void mx_env(t_ush *ush, char **command) {
    extern char **environ;
    char **unset = (char **)malloc(sizeof(char *) * mx_strarrlen(command));
    char **add_env = (char **)malloc(sizeof(char *) * (mx_strarrlen(command) + counter_add_env(command)));
    char **new_command = NULL;

    for (int i = 0; unset[i]; i++) {
        unset[i] = NULL;
    }
    for (int i = 0; add_env[i]; i++) {
        add_env[i] = NULL;
    }
    ush->flags = mx_create_env_flags();
    if (!command[1])
        print_env(environ);
    else {
        new_command = flags_trig(ush, &command[1], unset, add_env);
        if (!new_command)
            new_command = prepare_command(command, 0);
        env_process_creator(ush, new_command, unset, add_env);
    }
    free(ush->flags);
}
