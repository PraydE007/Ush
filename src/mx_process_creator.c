#include "../inc/ush.h"

static bool is_path(t_variable **list) {
    t_variable *pl = *list;

    while (pl) {
        if (mx_strcmp("PATH", pl->key) == 0)
            return true;
        pl = pl->next;
    }
    return false;
}

static void child_process(t_ush *ush, char **command) {
    char *proga = NULL;

    proga = mx_programm_finder(command[0]);
    if (getenv("PATH") != 0) {
        if (execvp(command[0], command) == -1)
            mx_error_making(command[0]);
    }
    else {
        if (is_path(&ush->variable_list) && proga) {
            mx_strdel(&command[0]);
            command[0] = mx_strdup(proga);
            mx_strdel(&proga);
        }
        if (execv(command[0], command) == -1)
            mx_error_making(command[0]);
    }
    exit(EXIT_FAILURE);
}

void mx_process_creator(t_ush *ush, char **command) {
    pid_t pid = 0;
    pid_t wpid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0)
        child_process(ush, command);
    else if (pid < 0)
        perror("ush");
    else if (pid > 0)
        wpid = waitpid(pid, &status, WUNTRACED);
}
