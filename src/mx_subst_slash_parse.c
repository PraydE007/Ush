#include "../inc/ush.h"

static void slash_handling(char **res, char *str, int *i) {
    int sl_num = mx_count_slashes(str);
    int exit_code = 0;

    if (sl_num == 1) {
        exit_code = mx_one_slash_s(res, str, i);
    }
    else if (sl_num == 2) {
        exit_code = mx_two_slash_s(res, str, i);
    }
    else if (sl_num == 3) {
        exit_code = mx_three_slash_s(res, str, i);
    }
    else if (sl_num == 4) {
        exit_code = mx_four_slash_s(res, str, i);
    }
}

void mx_subst_slash_parse(char **res, char *str, int *piv) {
    int i = 0;

    slash_handling(res, str, &i);
    (*piv) += i;
}
