#include "ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;
    char **line = NULL;
    extern char **environ;

    mx_read_environment(&ush->export_list, environ);
    while (ush->active) {
        if (!mx_read_input(ush)) {
            if (mx_parse_buf(ush)) {
                line = mx_str_dbl_split(ush->buf, ' ', ';');
                mx_check_commands(ush, line, environ);
                mx_del_strarr(&line);
                mx_dealloc_blocks(&(ush->blocks)); // DELETE ALL LISTS
                // PROCESSES
            }
        }
        if (!isatty(0)) // INPUT STUCK FIX
            ush->active = false;
    }
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush"); //
    return exit_code;
}
