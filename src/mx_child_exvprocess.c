#include "../inc/ush.h"

void mx_child_exvprocess(int *pipedes, int *pipedes2, int inout,
                        char **command) {
    if (inout == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
    }
    else {
        close(pipedes[1]);
        dup2(pipedes[0], 0);
        close(pipedes[0]);
    }
    close(pipedes2[0]);
    dup2(pipedes2[1], 2);
    close(pipedes2[1]);
    if (execvp(command[0], command) == -1)
        mx_error_making(command[0]);
    exit(EXIT_FAILURE);
}
