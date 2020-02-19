#include "libmx.h"

void mx_printint(int n) {
    if (n == -2147483648) {
        write(1, "-2147483648", 11);
    }
    else {
        if (n < 0) {
            mx_printchar('-');
            n *= -1;
        }
        if (n / 10 != 0) { 
            mx_printint(n / 10);
        }
        mx_printchar(n % 10 + 48);
    }
}
