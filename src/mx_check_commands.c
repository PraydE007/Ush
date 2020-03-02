#include "ush.h"

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

static bool is_builtin(t_ush *ush, char **command, char **env) {
        if (mx_strcmp("exit", command[0]) == 0) {
            ush->active = false;
            return true;
        }
        else if (mx_strcmp("export", command[0]) == 0) {
    //             t_export *export_list = NULL;
    // char **env = NULL;
    //         env = mx_read_environment(&export_list);
    //             setenv("JJJ", "!!!!!!!!!", 1);
    //             printf("env: \n");
    //             int i = 0;
    //             while (env[i]) {
    //                 printf("%s\n", env[i]);
    //                 i++;
                // }
            mx_export(command, env);
            return true;
        }
        else
            outlst(ush);
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
