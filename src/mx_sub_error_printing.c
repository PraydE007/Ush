#include "../inc/ush.h"

static void shell_name(char **sub) {
    if ((*sub)) {
        if ((*sub)[0] == 'z' && (*sub)[1] == 's' && (*sub)[2] == 'h') {
            (*sub)[0] = 'u';
            mx_printerr((*sub));
        }
    }
}

void mx_sub_error_printing(int *pipedes) {
    char *sub = mx_strnew(512);

    close(pipedes[1]);
    read(pipedes[0], sub, 512);
    if (sub) {
        shell_name(&sub);
        while (sub[0] != '\0') {
            mx_strdel(&sub);
            sub = mx_strnew(512);
            read(pipedes[0], sub, 512);
            shell_name(&sub);
        }
    }
    mx_strdel(&sub);
    close(pipedes[0]);
}
