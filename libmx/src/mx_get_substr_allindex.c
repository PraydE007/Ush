#include "libmx.h"

int mx_get_substr_allindex(const char *str, const char *subi, int count) {
    int j = 0;
    int k;

    if (str == NULL || subi == NULL)
        return -2;
    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == subi[j]) {
            k = i;
            while (str[k] == subi[j]) {
                if (j == mx_strlen(subi) - 1 && count == 0)
                    return i;
                k++;
                j++;
            }
            count--;
            j = 0;
        }
    }
    return -1;
}
