#include "../inc/ush.h"

static void slash_handling(char **res, char *str, int *piv) {
    int sl_num = mx_count_slashes(&str[*piv]);
    int wa = 0;

    if (sl_num == 1)
        wa = mx_one_slash_e(res, str, piv);
    else if (sl_num == 2)
        wa = mx_two_slash_e(res, str, piv);
    else if (sl_num == 3)
        wa = mx_three_slash_e(res, str, piv);
    else if (sl_num == 4)
        wa = mx_four_slash_e(res, piv);
}

static void parse_str(t_echo *flags, char **res, char **str, int st) {
    for (; str[st]; st++) {
        for (int i = 0; str[st][i] != '\0'; i++) {
            if (str[st][i] == '\\' && !(flags->E))
                slash_handling(res, str[st], &i);
            else
                mx_push_symbol_l(res, str[st][i]);
        }
        if (str[st + 1] && str[st + 1][0] != '\0')
            mx_push_symbol_l(res, ' ');
    }
}

static bool check_symbols(char *str) {
    int i = 0;

    while (str[i]) {
        if (str[i] >= 32 && 126 >= str[i])
            return true;
        i++;
    }
    return false;
}

static void end_of_line(t_ush *ush, t_echo *flags, char *res) {
    if (!(flags->n))
        mx_printchar('\n');
    else {
        if (!(ush->termconf->isInThread) && check_symbols(res)) {
            mx_printstr("\033[1;37;7m%\033[0m");
            for (int i = 0; i < ush->termconf->term_w; i++)
                mx_printchar(' ');
            mx_printchar('\r');
        }
    }
}

void mx_echo(t_ush *ush, char **arr) {
    char *res = mx_strnew_x(1);
    int st_pos = 1;
    t_echo *flags = mx_check_flags_echo(arr, &st_pos);

    parse_str(flags, &res, arr, st_pos);
    mx_printstr(res);
    end_of_line(ush, flags, res);
    mx_strdel(&res);
    free(flags);
    ush->exit_code = 0;
}
