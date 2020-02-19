#include "libmx.h"

int mx_sqrt(int x) {
    int sqrt = 0;

    for (int i = 1; i <= x / 2 + 1; i++) {
        if (i * i == x)
            sqrt = i;
    }
    return sqrt;
}
