#include "../inc/ush.h"

static int check_correction(char *str) {
    if (mx_strcmp(str, "\0") == 0)
        return 0;
    return 1;
}

int mx_history_handler(t_termconf **cfg, char *str) {
    int exit_code = 0;

    if (check_correction(str)) {
        mx_push_h_node_back(&((*cfg)->h_node), str);
    }
    else {
        mx_strdel(&str);
        (*cfg)->h_len -= 1;
        exit_code = 1;
    }
    return exit_code;
}
