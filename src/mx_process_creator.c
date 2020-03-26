#include "../inc/ush.h"

static bool slash_checking(char *comn) {
    for (int i = 0; comn[i]; i++) {
        if (comn[i] == '/')
            return true;
    }
    return false;
}

static void error_printing(char *comn) {
    if (!slash_checking(comn)) {
        mx_printerr("ush: command not found: ");
        mx_printerr(comn);
        mx_printerr("\n");
    }
    else {
        mx_printerr("ush: no such file or directory: ");
        mx_printerr(comn);
        mx_printerr("\n");
    }
}

static void process_error(char *comn) {
    if (errno == 2) {
        errno = 0;
        error_printing(comn);
        exit(127);
    }
    else {
        errno = 0;
        perror("ush");
        exit(126);
    }
}

static bool is_path(t_variable **list) {
    t_variable *pl = *list;

    while (pl) {
        if (mx_strcmp("PATH", pl->key) == 0)
            return true;
        pl = pl->next;
    }
    return false;
}

void mx_process_creator(t_ush *ush, char **command) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;
    char *proga = NULL;

    proga = mx_programm_finder(command[0]);
    pid = fork();
    if (pid == 0) {
        if (getenv("PATH") != 0) {
            if (execvp(command[0], command) == -1)
                process_error(command[0]);
        }
        else if (is_path(&ush->variable_list) && proga) {
            mx_strdel(&command[0]);
            command[0] = mx_strdup(proga);
            mx_strdel(&proga);
            if (execv(command[0], command) == -1)
                process_error(command[0]);
        }
        else {
            if (execv(command[0], command) == -1)
                process_error(command[0]);
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        perror("ush");
    }
    else if (pid > 0) {
        wpid = waitpid(pid, &status, WUNTRACED);
        // while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
        //     wpid = waitpid(pid, &status, WUNTRACED);
        // }
    }
    mx_strdel(&proga);
}
