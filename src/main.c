#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;
    int func_exit = 0;

    mx_sig_init();
    mx_constant_variables(ush);
    while (ush->active) {
        if (!(func_exit = mx_read_input_pro(ush))) {
            mx_parse_buf(ush);
            //1
            //printf("ush->exit_code_main: %d\n", ush->exit_code);
            //2
        }
        else if (func_exit == 101) {
            ush->active = false;
            ush->exit_code = 1;
        }
        mx_del_clone_history(&(ush->termconf));
    }
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
