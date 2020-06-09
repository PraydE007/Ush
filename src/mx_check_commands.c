#include "../inc/ush.h"

static bool is_dir(char ***comn) {
    struct stat statbuf;

    if (stat((*comn)[0], &statbuf) != -1 || mx_strcmp((*comn)[0], " ") == 0) {
        if (S_ISDIR(statbuf.st_mode) || mx_strcmp((*comn)[0], " ") == 0) {
            if (mx_strcmp((*comn)[0], ".") == 0)
                mx_printerr(".: not enough arguments\n");
            else {
                mx_printerr("ush: permission denied: ");
                if (mx_strcmp((*comn)[0], " ") == 0)
                    mx_printerr("");
                else
                    mx_printerr((*comn)[0]);
                mx_printerr("\n");
            }
                mx_del_strarr(comn);
            return true;
        }
    }
    return false;
}

void mx_check_commands(t_ush *ush, t_b_node *block) {
    char **comn = NULL;
    char ***pipemat = NULL;

    comn = mx_command_matrix_creator(&block->t_node);
    if (is_dir(&comn))
        return;
    else if (mx_is_pipe(comn, NULL)) {
        pipemat = mx_pipe_matrix_creator(ush, comn);
        pipemat ? mx_pipe_process_creator(ush, pipemat) : (void)0;
    }
    else
        mx_is_builtin(ush, comn) ? (void)0 : mx_process_creator(ush, comn);
    mx_del_strarr(&comn);
    mx_del_strararr(&pipemat);
}
