#include "../inc/libmx.h"

bool mx_isupper(int c) {
    bool y;

    if (c > 64 && c < 91) {
        y = true;
    }
    else {
        y = false;
    }
    return y;
}
