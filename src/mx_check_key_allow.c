#include "../inc/ush.h"

bool mx_check_key_allow(t_ush *ush, char *kay) {
    int i = 0;

    if (ush != NULL) {
        if (kay[0] < 65 || (kay[0] > 90 && kay[0] < 97 && kay[0] != 95)
            || kay[0] > 122) {
                ush->trigger = true;
                return false;
            }
    }
    while (kay[i]) {
        if ((kay[i] < 48 || (kay[i] > 57 && kay[i] < 65)
            || (kay[i] > 90 && kay[i] < 97) || kay[i] > 122)
            && (kay[i] != 36 && kay[i] != 95)) {
            return false;
        }
        i++;
    }
    return true;
}
