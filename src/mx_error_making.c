#include "../inc/ush.h"


static void error_end(char *comn) {
    mx_printerr(comn);
    mx_printerr("\n");
}

static void error_printing(char *comn) {
    if (mx_strcmp(comn, "/") == 0 || mx_strcmp(comn, "..") == 0
            || mx_strcmp(comn, "./") == 0 || mx_strcmp(comn, "/.") == 0) {
        mx_printerr("ush: permission denied: ");
        error_end(comn);
    }
    else if (comn[1] && mx_is_slash(comn)) {
        mx_printerr("ush: no such file or directory: ");
        error_end(comn);
    }
    else if (mx_strcmp(comn, ".") == 0)
        mx_printerr(".: not enough arguments\n");
    else if (comn[0] == ' ') {
        mx_printerr("ush: no such user or named directory: ");
        error_end(&comn[1]);
    }
    else {
        mx_printerr("ush: command not found: ");
        error_end(comn);
    }
}

void mx_error_making(char *comn) {
    if (errno == 2) {
        errno = 0;
        error_printing(comn);
        exit(127);
    }
    else {
        errno = 0;
        error_printing(comn);
        exit(126);
    }
}
