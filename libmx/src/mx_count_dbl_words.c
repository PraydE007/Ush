#include "libmx.h"

int mx_count_dbl_words(const char *str, char c, char b) {
    int count = 0;
    int size;

    if (str == NULL)
        return -1;
    size = mx_strlen(str);
    for (int i = 0; i < size; i++) {
        if ((str[i] == c || str[i] == b) && (str[i+1] != '\0'
            && str[i+1] != c && str[i+1] != b)) {
            count++;
        }
    }
    if (str[0] != c && str[0] != b)
        count++;
    return count;
}
