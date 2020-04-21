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

static void dir_error_printing(char *command) {
    mx_printerr("ush: permission denied: ");
    if (mx_strcmp(command, "/") == 0)
        mx_printerr("");
    else
        mx_printerr(command);
    mx_printerr("\n");
}

void mx_check_commands(t_ush *ush) {
    struct stat statbuf;
    t_b_node *block = ush->blocks;
    char **command = NULL;

    while (block) { // MAYBE NOT NEEDED
        command = mx_command_matrix_creator(&block->t_node);
        if (stat(command[0], &statbuf) != -1) {
            if (S_ISDIR(statbuf.st_mode )) {
                dir_error_printing(command[0]);exit
                mx_del_strarr(&command);
                break;
            }
        }
        is_builtin(ush, command) ? 0 : mx_process_creator(ush, command);
        mx_del_strarr(&command);
        block = block->next;
    }
}
