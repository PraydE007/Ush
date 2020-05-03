#include "../inc/ush.h"

static bool first_part_of_biltin(t_ush *ush, char **command) {
    if (mx_strcmp("exit", command[0]) == 0) {
        ush->exit_code = mx_exit(command);
        ush->active = false;
        return true;
    }
    // else if (mx_strcmp("env", command[0]) == 0) {
    //     mx_env(ush, command);
    //     return true;
    // }
    else if (mx_strcmp("export", command[0]) == 0) {
        mx_export(ush, command);
        return true;
    }
    else if (mx_strcmp("unset", command[0]) == 0) {
        mx_unset(command, ush);
        return true;
    }
    return false;
}

static bool second_part_of_biltin(t_ush *ush, char **command) {
    if (mx_strcmp("history", command[0]) == 0) {
        mx_print_history(ush->termconf);
        return true;
    }
    else if (mx_strcmp("termcol", command[0]) == 0) {
        mx_change_color(ush, command);
        return true;
    }
    else if (mx_strcmp("clear", command[0]) == 0) {
        mx_printstr("\x1B[0;0H\x1B[0J");
        return true;
    }
    else if (mx_strcmp("which", command[0]) == 0) {
        mx_which(ush, command);
        return true;
    }
    return false;
}

static bool is_builtin(t_ush *ush, char **command) {
    // mx_outlst(ush);
    if (first_part_of_biltin(ush, command))
        return true;
    else if (second_part_of_biltin(ush, command))
        return true;
    else {
        char **kv = mx_key_value_creation(ush, command[0]);

        if (kv != NULL || ush->equals) {
            if (kv != NULL) {
                mx_adding_variable(ush, command, kv);
                mx_del_strarr(&kv);
            }
            ush->equals = false;
            return true;
        }
    }
    return false;
}

static void child_recursion(t_ush *ush, char ***commatrix, int *pipedes, int *pipedes2) {
        dup2(pipedes[0], 0);
        close(pipedes[0]);
        if (commatrix[ush->i + 1]) {
            close(pipedes2[0]);
            dup2(pipedes2[1], 1);
            close(pipedes2[1]);
        }
        mx_child_process(ush, commatrix[ush->i]);
}

static void pipe_creator(t_ush *ush, char ***commatrix, int *pipedes) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes2[2];

    ush->i = ush->i + 1;
    close(pipedes[1]);
    pipe(pipedes2);
    pid = fork();
    if (pid == 0)
        child_recursion(ush, commatrix, pipedes, pipedes2);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0) {
        if (commatrix[ush->i + 1])
            pipe_creator(ush, commatrix, pipedes2);
        else
            wpid = waitpid(pid, &status, WUNTRACED);
    }
}

// A LOT OF LINES
void mx_pipe_process_creator(t_ush *ush, char ***commat) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    int pipedes[2];

    if (commat[1]) {
    pipe(pipedes);
    pid = fork();
    if (pid == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
        mx_child_process(ush, commat[ush->i]);
    }
    else if (pid < 0)
        perror("ush");
    else if (pid > 0 )
        pipe_creator(ush, commat, pipedes);
    }
    else
        is_builtin(ush, commat[0]) ? 0 : mx_process_creator(ush, commat[0]);
    ush->i = 0;
}
