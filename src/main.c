#include "../inc/ush.h"

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

    mx_constant_variables(ush);
        while (ush->active) {
            if (!mx_read_input(ush)) {
                if (mx_parse_buf(ush)) {
                    mx_check_commands(ush);
                    mx_dealloc_blocks(&(ush->blocks)); // DELETE ALL LISTS
                    // PROCESSES
                }
                if (!isatty(0)) // INPUT STUCK FIX
                    ush->active = false;
            }
            while (ush->termconf->clone)
                mx_pop_h_node_front(&(ush->termconf->clone));
        }
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush");
    return exit_code;
}
