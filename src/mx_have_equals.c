#include "../inc/ush.h"

bool mx_have_equals(t_ush *ush, char *env) {
    int i = 0;

    while (env[i]) {
        if (env[0] == '='
            || (env[i] == '=' && env[i + 1] == '=' && env[i + 2])) {
            mx_printerr("ush: ");
            if (!ush->equals) {
                if (env[0] == '=')
                    mx_printerr(&env[0]);
                else
                    mx_printerr(&env[i + 2]);
                mx_printerr(" not found\n");
                ush->equals = true;
            }
            return false;
        }
        if (i != 0 && env[i] == '=')
            return true;
        i++;
    }
    return false;
}
