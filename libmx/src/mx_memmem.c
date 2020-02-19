#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little,
                                                        size_t little_len) {
    char *p_big = (char *) big;
    char *p_little = (char *) little;

    if(big_len < little_len || big_len == 0 || little_len == 0)
        return NULL;
    for (size_t i = 0; i < big_len; i++) {
        if (*p_big == p_little[0]) {
            if (mx_memcmp(p_big, p_little, little_len) == 0)
                return p_big;
        }
        p_big++;
    }
    return NULL;
}
