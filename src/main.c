#include "ush.h"

// FUNCTION ON SOME TIME
static void check_some_commands(t_ush *ush) {
    if (mx_strcmp("exit", ush->buf) == 0)
        ush->active = false;
}

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

    while (ush->active) {
        mx_read_input(ush);
        check_some_commands(ush);
        // PARSE
        // PROCESSES
    }

    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    // system("leaks -q ush"); //
    return exit_code;
}
