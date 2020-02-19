#include "libmx.h"

char *mx_spacedel(char *newstr, const char *str) {
    int j = 0;
    int size = mx_strlen(str);

    for (int i = 0; i < size; i++) {
        if (mx_isspace(str[i-1])) {
            while(mx_isspace(str[i]))
                i++;
        }
        newstr[j] = str[i];
        j++;
    }
    return newstr;
}
