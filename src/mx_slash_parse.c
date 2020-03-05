#include "ush.h"

static int slash_handling(char **res, char *str, int *i, int *res_size) {
    int sl_num = mx_count_slashes(str);

    if (sl_num == 1) {
        if (!mx_one_slash(res, str, i, res_size))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 2) {
        if (!mx_two_slash(res, str, i, res_size))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 3) {
        if (!mx_three_slash(res, str, i, res_size))
            return mx_break_on_error(res) == NULL ? 0 : 0;
    }
    else if (sl_num == 4) {
        (*i) += 3;
        mx_push_symbol(res, '\\', res_size);
    }
    return 1;
}

char *mx_slash_parse(char *str, int *piv) {
    char *res = mx_strnew_x(1);
    int len = mx_strlen(str);
    int res_size = 1;
    int i = 0;

    if (!slash_handling(&res, str, &i, &res_size))
        return NULL;
    (*piv) += i;
    return res;
}
