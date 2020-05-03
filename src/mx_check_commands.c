#include "../inc/ush.h"

static void dir_error_printing(char *command) {
    if (mx_strcmp(command, ".") == 0)
        mx_printerr(".: not enough arguments\n");
    else {
        mx_printerr("ush: permission denied: ");
        if (mx_strcmp(command, " ") == 0)
            mx_printerr("");
        else
            mx_printerr(command);
        mx_printerr("\n");
    }
}
// A LOT OF LINES
void mx_check_commands(t_ush *ush) {
    struct stat statbuf;
    t_b_node *block = ush->blocks;
    char **command = NULL;
    char ***pipemat = NULL;

    while (block) { // MAYBE NOT NEEDED
        command = mx_command_matrix_creator(&block->t_node);
        if (stat(command[0], &statbuf) != -1
            || mx_strcmp(command[0], " ") == 0) {
            if (S_ISDIR(statbuf.st_mode) || mx_strcmp(command[0], " ") == 0) {
                dir_error_printing(command[0]);
                mx_del_strarr(&command);
                break;
            }
        }
        if (mx_is_pipe(command, NULL)) {
            pipemat = mx_pipe_matrix_creation(ush, command);
            if (pipemat)
                mx_pipe_process_creator(ush, pipemat);
        }
        else
            mx_is_builtin(ush, command) ? 0 : mx_process_creator(ush, command);
        mx_del_strarr(&command);
        mx_del_strararr(&pipemat);
        block = block->next;
    }
}
