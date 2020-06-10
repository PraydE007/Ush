#include "../inc/ush.h"

static void env_filler(char **env, char **unset, char **environ, int lll) {
    int j = 0;
    int flag = 1;
    char **buf = NULL;

    for (int i = 0; i < lll; i++)
        env[i] = NULL;
    for (int i = 0; environ[i]; i++) {
        for (int y = 0; unset[y]; y++) {
            buf = mx_strsplit(environ[i], '=');
            if (!strcmp(unset[y], buf[0]) && strcmp(buf[0], "_")) {
                flag = 0;
            }
            mx_del_strarr(&buf);
        }
        if (flag == 1) {
            env[j] = mx_strdup(environ[i]);
            j++;
        }
        flag = 1;
    }
}

static int check_for_P(char *path, char *exe) {
    char *command = mx_strjoin(path, exe);
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

static void flag_P(char **com, t_ush *ush, char **env, int i) {
    if (ush->flags->i) {
        if (execve(mx_strjoin(com[0], com[1]), &com[1], NULL) == -1)
            perror("ush");
        exit(1);
    }
    else if (check_for_P(com[0], com[1])) {
        char *res = mx_strjoin(com[0], com[1]);
        if (execve(res, &com[1], env) == -1)
            perror("ush");
        exit(1);
    }
    else if (ush->flags->i) {
        if (execve(mx_strjoin(com[0], com[1]), &com[1], NULL) == -1)
            perror("ush");
        exit(1);
    }
    else {
        if (execve(mx_strjoin(com[0], com[i]), &com[i], env) == -1)
            perror("ush");
        exit(1);
    }
}

static void main_part(char **command, char **env, t_ush *ush, int i) {
    if (ush->flags->P)
        flag_P(command, ush, env, i);
    else if (ush->flags->i) {
        if (execve(mx_which_str(command[i]), &command[i], NULL) == -1)
            perror("ush");
        exit(1);
    }
    else {
        if (check_for_P(NULL, command[0]) == 2) {
            if (execve(mx_which_str(command[0]), command, env) == -1)
                perror("ush");
            exit(1);
        }
        else if (execve(mx_which_str(command[0]), command, env) == -1)
            perror("ush");
        exit(1);
    }
}

void mx_env_process_creator(t_ush *ush, char **command, char **unset, int i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    extern char **environ;
    char **env = (char **)malloc(sizeof(char *) * (mx_strarrlen(environ) + 1));

    env_filler(env, unset, environ, mx_strarrlen(environ) + 1);
    pid = fork();
    if (pid == 0)
        main_part(command, env, ush, i);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        wpid = waitpid(pid, &status, WUNTRACED);
        if (WIFEXITED(status))
            ush->exit_code = 0;
        if (status != 0)
            ush->exit_code = 1;
    }
    env[mx_strarrlen(environ)] = NULL;
    mx_del_strarr(&env);
}
