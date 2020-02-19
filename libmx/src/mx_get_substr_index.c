#include "libmx.h"

int mx_get_substr_index(const char *str, const char *subi) {
    int j = 0;
    int k;

    if (str == NULL || subi == NULL)
        return -2;
    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == subi[j]) {
            k = i;
            while (str[k] == subi[j]) {
                if (j == mx_strlen(subi) - 1)
                    return i;
                k++;
                j++;
            }
            j = 0;
        }
    }
    return -1;
}
