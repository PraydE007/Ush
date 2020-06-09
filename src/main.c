#include "../inc/ush.h"

static void main_cycle(t_ush *ush) {
    int func_exit = 0;

    if (!(func_exit = mx_read_input_pro(ush)))
        mx_parse_buf_pro(ush);
    else if (func_exit == 101)
        mx_printchar('\n');
    else if (func_exit == 102) {
        ush->active = false;
        ush->exit_code = 1;
    }
}

int main() {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

    mx_sig_init();
    mx_constant_variables(ush);
    while (ush->active) {
        main_cycle(ush);
        mx_del_clone_history(&(ush->termconf));
    }
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
