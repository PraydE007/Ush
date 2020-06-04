#include "../inc/ush.h"

void mx_cntrl_z_printing(char **command) {
    mx_printstr("\nush: suspended  ");
    for (int i = 0; command[i]; i++) {
        mx_printstr(command[i]);
        if (command[i + 1])
            mx_printstr(" ");
    }
    mx_printstr("\n");
}
