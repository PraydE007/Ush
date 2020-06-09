#include "../inc/ush.h"

short cases_part_two(unsigned char *ch) {
    if (32 <= ch[0] && ch[0] <= 126)
        return 0;
    else if (ch[0] == 127)
        return 1;
    else if (ch[0] == 3)
        return 101;
    else if (ch[0] == 4)
        return 102;
    return -1;
}

short cases_part_one(unsigned char *ch) {
    if (ch[1] == 91) {
        if (ch[2] == 68)
            return 2;
        else if (ch[2] == 67)
            return 3;
        else if (ch[2] == 65)
            return 4;
        else if (ch[2] == 66)
            return 5;
    }
    return -1;
}

short mx_get_buf_type(unsigned char *ch) {
    int res = 0;

    if (ch[0] == 27) {
        if ((res = cases_part_one(ch)) != -1)
            return res;
    }
    else {
        if ((res = cases_part_two(ch)) != -1)
            return res;
    }
    return -1;
}
