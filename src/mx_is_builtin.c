#include "../inc/ush.h"

static bool first_part_of_biltin(t_ush *ush, char **command) {
    if (mx_strcmp("exit", command[0]) == 0) {
        ush->exit_code = mx_exit(command);
        ush->active = false;
        return true;
    }
//    else if (mx_strcmp("env", command[0]) == 0) {
//        mx_env(ush, command);
//        return true;
//    }
    //else if (mx_strcmp("echo", command[0]) == 0) {
    //    mx_echo(ush, command);
    //    return true;
    //}
    else if (mx_strcmp("export", command[0]) == 0) {
        mx_export(ush, command);
        return true;
    }
    else if (mx_strcmp("unset", command[0]) == 0) {
        mx_unset(command, ush);
        return true;
    }
    else if (mx_strcmp("fg", command[0]) == 0) {
        mx_fg(ush, command);
        return true;
    }
    else if (mx_strcmp("jobs", command[0]) == 0) {
        mx_jobs(ush);
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
    else if (mx_strcmp("cd", command[0]) == 0) {
        mx_cd(command, ush);
        return true;
    }
    return false;
}

bool mx_is_builtin(t_ush *ush, char **command) {
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
