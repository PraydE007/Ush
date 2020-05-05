#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;
    int func_exit = 0;

    mx_constant_variables(ush);
    while (ush->active) {
        if (!(func_exit = mx_read_input(ush)))
            mx_parse_buf(ush);
        else if (func_exit == 101) {
            ush->active = false;
            ush->exit_code = 1;
        }
        while (ush->termconf->clone)
            mx_pop_h_node_front(&(ush->termconf->clone));
    }
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
