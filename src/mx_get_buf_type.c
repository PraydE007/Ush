#include "../inc/ush.h"

short mx_get_buf_type(char ch) {
    if (32 <= ch && ch <= 126)
        return 0;
    else
        return 1;
}
