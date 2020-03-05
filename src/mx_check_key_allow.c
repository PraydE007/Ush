#include "../inc/ush.h"

bool mx_check_key_allow(char **kv) {
    int i = 0;

    while (kv[0][i]) {
        if ((kv[0][i] < 48 || (kv[0][i] > 57 && kv[0][i] < 65)
            || (kv[0][i] > 90 && kv[0][i] < 97) || kv[0][i] > 122)
            && (kv[0][i] != 36 && kv[0][i] != 95)) {
            return false;
        }
        i++;
    }
    return true;
}
