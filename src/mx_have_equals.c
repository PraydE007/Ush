#include "../inc/ush.h"

bool mx_have_equals(char *env) {
    int i = 0;

    while (env[i]) {
        if (env[i + 2]) {
            if (env[i] == '=' && env[i + 1] == '=') {
                mx_printerr("ush: ");
                mx_printerr(&env[i + 2]);
                mx_printerr(" not found\n");
                return false;
            }
        }
        if (env[i] == '=')
            return true;
        i++;
    }
    return false;
}
