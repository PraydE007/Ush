#include "ush.h"

char *mx_break_on_error(char **str) {
    mx_strdel(str);
    return NULL;
}
