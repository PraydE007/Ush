#include <stdbool.h>

bool mx_islower(int c) {
    bool y;

    if (c > 96 && c < 123) {
        y = true;
    }
    else {
        y = false;
    }
    return y;
}

