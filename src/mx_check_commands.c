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

static bool is_builtin(t_ush *ush, char **comn, char **env) {
        if (mx_strcmp("exit", comn[0]) == 0) {
            ush->active = false;
            return true;
        }
        else if (mx_strcmp("export", comn[0]) == 0) {
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
            mx_export(&ush->export_list, comn, env);
            return true;
        }
        else
            outlst(ush);
    return false;
}

void mx_check_commands(t_ush *ush, char **line, char **env) {
    // for (int i = 0; list_line; list_line = list_line->next) {
        is_builtin(ush, line, env) ? 0 : mx_process_creator(line);
    // }
    
}
