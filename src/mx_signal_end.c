#include "../inc/ush.h"

static void cntrl_z_printing(char ***commat) {
    mx_printstr("\nush: suspended  ");
    for (int i = 0; commat[i]; i++) {
        for (int j = 0; commat[i][j]; j++) {
            mx_printstr(commat[i][j]);
            if (commat[i][j + 1])
                mx_printstr(" ");
        }
        if (commat[i + 1])
            mx_printstr(" | ");
    }
    mx_printstr("\n");
}

void mx_signal_end(char ***commat, int status) {
    // if (WIFEXITED(status))
    //     error_number = 0;
    // else 
    if (WIFSTOPPED(status)) {
        // error_number = 146;
        cntrl_z_printing(commat);
    }
    else if (WTERMSIG(status)) {
        // error_number = 130;
        mx_printstr("\n");
    }
    // else if (status != 0)
        // error_number = 1;

}
