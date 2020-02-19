#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    int arsize = 0;
    unsigned long dec = 0;
    unsigned long pow = 1;

    while (hex[arsize])
        arsize++;
    for (int i = arsize - 1; i >= 0; i--) {
        if (hex[i] > 64 && hex[i] < 71)
            dec += (hex[i] - 55) * pow;
        else if (hex[i] > 96 && hex[i] < 103)
            dec += (hex[i] - 87) * pow;
        else if (hex[i] > 47 && hex[i] < 58)
            dec += (hex[i] - 48) * pow;
        else
            return 0;
        pow *= 16;
    }
    return dec; 
}
