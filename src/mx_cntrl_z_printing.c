#include "../inc/ush.h"

void mx_cntrl_z_printing(char **command) {
    mx_printerr("\nush: suspended  ");
    for (int i = 0; command[i]; i++) {
        mx_printerr(command[i]);
        if (command[i + 1])
            mx_printerr(" ");
    }
    mx_printerr("\n");
}
