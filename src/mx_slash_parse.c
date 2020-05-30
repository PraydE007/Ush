#include "../inc/ush.h"

static int slash_handling(char **res, char *str, int *i) {
    int sl_num = mx_count_slashes(str);

    if (sl_num == 1) {
        if (!mx_one_slash(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 2) {
        if (!mx_two_slash(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 3) {
        if (!mx_three_slash(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 4) {
        if (!mx_four_slash(res, str, i))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    return 1;
}

char *mx_slash_parse(char *str, int *piv) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int i = 0;

    if (!slash_handling(&res, str, &i))
        return NULL;
    (*piv) += i;
    return res;
}
