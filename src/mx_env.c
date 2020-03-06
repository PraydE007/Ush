#include "../inc/ush.h"

static void print_env(char **env) {
    for (int i = 0; env[i]; i++) {
        mx_printstr(env[i]);
        mx_printchar('\n');
    }
}

static void env_process_creator(char **command, char **env, int i) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0) {
        if (execve(command[i], &command[i], env) == -1)
            perror("ush");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("ush");
    }
    else if (pid > 0) {
        wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
    }
}

//static void flags_trig(char **command, t_env_flags *flags) {
//    if (command[1]) {
//        for (int j = 1; command[1][j]; j++) {
//            if (command[1][0] == '-') {
//                if (command[j] == 'P') {
//                    flags->P = 1;
//                    break;
//                }
//                else if (command[j] == 'i') {
//                    flags->i = 1;
//                    break;
//                }
//                else if (command[j] == 'u') {
//                    flags->u = 1;
//                    break;
//                }
//            }
//        }
//    }
//}

void mx_env(char **command, char **env) {
    if (!command[1])
        print_env(env);
    for (int i = 1; command[i]; i++) {
        if (command[i][0] != '-') {
            env_process_creator(command, env, i);
            break;
        }
    }
}