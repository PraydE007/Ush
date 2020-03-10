#include "../inc/ush.h"

short mx_get_buf_type(unsigned char *ch) {
    if (!ch[1] && !ch[2] && !ch[3]) {
        if (32 <= ch[0] && ch[0] <= 126)
            return 0;
        else
            return 1;
    }
    else {
        if (ch[0] == 27 && ch[1] == 91 && !ch[3]) {
            if (ch[2] == 68)
                return 2;
            else if (ch[2] == 67)
                return 3;
            else if (ch[2] == 65)
                return 4;
            else if (ch[2] == 66)
                return 5;
        }
    }
    return 1;
}
