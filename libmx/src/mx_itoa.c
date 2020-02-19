#include "libmx.h"

char *mx_itoa(long long number) {
    char *toa = NULL;
    long long size = 0;
    long long temp = number;
    long long i = 0;

    size = mx_nbrlen(number);
    toa = mx_strnew(size);
    if (number < 0) {
        temp *= -1;
        toa[i] = '-';
        i++;
    }
    for (long long j = size - 1; j >= i; j--) {
        toa[j] = temp % 10 + 48;
        temp = temp / 10;
    }
    return toa;
}
