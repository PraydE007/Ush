#include "../inc/ush.h"
//CHECK IF WE NEED COMMENTED
void mx_child_exvprocess(t_ush *ush, int *pipedes, int *pipedes2,
                                                            char **command) {
    // if (inout == 0) {
        close(pipedes[0]);
        dup2(pipedes[1], 1);
        close(pipedes[1]);
    // }
    // else {
    //     close(pipedes[1]);
    //     dup2(pipedes[0], 0);
    //     close(pipedes[0]);
    // }
    close(pipedes2[0]);
    dup2(pipedes2[1], 2);
    close(pipedes2[1]);
    if (execvp(command[0], command) == -1)
        mx_error_making(ush, command[0]);
    exit(EXIT_FAILURE);
}
