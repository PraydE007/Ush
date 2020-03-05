#include "../inc/ush.h"

static void outlst(t_ush *ush) {
    t_b_node *block = ush->blocks;
    t_t_node *x = NULL;

    while (block) {
        x = block->t_node;
        while (x != NULL) {
            fprintf(stdout, "\x1b[32m [\x1b[0m %s \x1b[32m]\x1b[0m ", x->text);
            fflush(stdout);
            x = x->next;
        }
        mx_printstr("\n");
        block = block->next;
    }
    fprintf(stdout, "\n");
}
// do kv ONLY IN ELSE
static bool is_builtin(t_ush *ush, char **command, char **env) {
    char **kv = mx_key_value_creation(ush, command[0]);

    if (mx_strcmp("exit", command[0]) == 0) {
        ush->exit_code = mx_exit(command);
        ush->active = false;
        mx_del_strarr(&kv);
        return true;
    }
    else if (mx_strcmp("export", command[0]) == 0) {
        mx_export(ush, command, env);
        mx_del_strarr(&kv);
        return true;
    }
    else if (mx_strcmp("unset", command[0]) == 0) {
        mx_unset(command, env, ush);
        mx_del_strarr(&kv);
        return true;
    }
    else if (kv != NULL || ush->equals) {
        if (kv != NULL) {
            mx_adding_variable(ush, command, kv);
            mx_del_strarr(&kv);
        }
        ush->equals = false;
        return true;
    }
    else
        outlst(ush);
    mx_del_strarr(&kv);
    return false;
}

void mx_check_commands(t_ush *ush, char **env) {
    t_b_node *block = ush->blocks;
    char **command = NULL;

    while (block) {
        command = mx_command_matrix_creator(&block->t_node);
        is_builtin(ush, command, env)
        ? 0 : mx_process_creator(command);
        mx_del_strarr(&command);
        block = block->next;
    }
}
