#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int j = 0;
    int k;
    int count = 0;

    if (str == NULL || sub == NULL)
        return -1;
    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == sub[j]) {
            k = i;
            while (str[k] == sub[j]) {
                if (j == mx_strlen(sub) - 1)
                    count++;
                k++;
                j++;
            }
            j = 0;
        }
    }
    return count;
}
