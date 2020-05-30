#include "../inc/ush.h"

bool mx_is_control_slash(char ch) {
    if (ch == 'a')
        return true;
    else if (ch == '0')
        return false;
    else if (ch == 'b')
        return true;
    else if (ch == 't')
        return true;
    else if (ch == 'n')
        return true;
    else if (ch == 'v')
        return true;
    else if (ch == 'f')
        return true;
    else if (ch == 'r')
        return true;
    return false;
}
