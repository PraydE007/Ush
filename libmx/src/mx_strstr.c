#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int j = 0;
    int k;

    for (int i = 0; i < mx_strlen(haystack); i++) {
        if (haystack[i] == needle[0]) {
            k = i;
            while (haystack[k] == needle[j]) {
                if (j == mx_strlen(needle) - 1)
                    return (char *)&haystack[i];
                k++;
                j++;
            }
            j = 0;
        }
    }
    return 0;
}
