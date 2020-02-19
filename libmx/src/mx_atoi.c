#include "libmx.h"

int mx_atoi(const char *str) {
    int i = 0;
    int sign = 1;
    int res = 0;

    while (mx_isspace(str[i]) == 1) {
        i++;
    }
    if ((str[i] == '-' || str[i] == '+')
        && mx_isdigit(str[i+1]) == 1) {
        if (str[i] == '-') {
            sign = -1;
        }
        i++;
    }
    while (mx_isdigit(str[i])) {
        res = res * 10 + (str[i] - 48);
        i++;
    }
    return res * sign;
}
