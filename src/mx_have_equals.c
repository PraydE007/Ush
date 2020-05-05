#include "../inc/ush.h"

bool mx_have_equals(t_ush *ush, char *ev) {
    int i = 0;

    while (ev[i]) {
        if (ev[0] == '=' || (ev[i] == '=' && ev[i + 1] == '=' && ev[i + 2])) {
            mx_printerr("ush: "); //check maybe it must be one line down
            if (!ush->equals) {
                if (ev[0] == '=')
                    mx_printerr(&ev[0]);
                else
                    mx_printerr(&ev[i + 2]);
                mx_printerr(" not found\n");
                ush->equals = true;
            }
            return false;
        }
        if (i != 0 && ev[i] == '=')
            return true;
        i++;
    }
    return false;
}
