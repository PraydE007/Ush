#include "ush.h"

static void out_parsed(t_ush *ush) {
    t_b_node *block = ush->blocks;
    t_t_node *x = NULL;

    while (block) {
        x = block->t_node;
        while (x != NULL) {
            mx_printstr(x->text);
            mx_printstr("\n");
            x = x->next;
        }
        block = block->next;
    }
}

// FUNCTION ON SOME TIME
static int check_some_commands(t_ush *ush) {
    if (mx_strcmp("exit", ush->buf) == 0) {
        ush->active = false;
        return 1;
    }
    out_parsed(ush); // PARSING TEST FUNCTION
    return 0;
}

int main(int argc, char *argv[]) {
    t_ush *ush = mx_create_ush();
    int exit_code = 0;

    while (ush->active) {
        if (!mx_read_input(ush)) {
            mx_parse_buf(ush);
            check_some_commands(ush);
            mx_dealloc_blocks(&(ush->blocks)); // DELETE ALL LISTS
            // PROCESSES
        }
        if (!isatty(0)) // INPUT STUCK FIX
            ush->active = false;
    }
    exit_code = ush->exit_code;
    mx_dealloc_ush(&ush);
    system("leaks -q ush"); //
    return exit_code;
}
