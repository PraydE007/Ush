#include "ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;
    char **line = NULL;
    // char *str = NULL;
    extern char **environ;

   mx_read_environment(&ush->export_list, environ);
    // mx_export(&export_list, command, env);
    // str = getenv("PATH");
    // printf("%s\n", str);
    while (ush->active) {
        mx_read_input(ush);
        line = mx_str_dbl_split(ush->buf, ' ', ';');
        mx_check_commands(ush, line, environ);
        // PARSE
        // PROCESSES
        mx_del_strarr(&line);
    }

    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
