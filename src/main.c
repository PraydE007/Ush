#include "ush.h"

// FUNCTION ON SOME TIME
static int check_some_commands(t_ush *ush) {
    if (mx_strcmp("exit", ush->buf) == 0) {
        ush->active = false;
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    t_t_node *head = NULL;

    mx_push_t_node_back(&(head), "ls -la");
    mx_push_t_node_back(&(head), "echo\'A\\B\' \'A\\B\'X\'A\\B\'");
    //mx_push_t_node_back(&(head), "ABC lol \'A\"B\'");
    mx_parse_block(&head);

    // t_ush *ush = mx_create_ush();
    // int exit_code = 0;

    // while (ush->active) {
    //     if (!mx_read_input(ush)) {
    //         check_some_commands(ush);
    //         mx_parse_buf(ush);
    //         // PROCESSES
    //     }
    // }
    // exit_code = ush->exit_code;
    // mx_dealloc_ush(&ush);
    // system("leaks -q ush"); //
    // return exit_code;
}
