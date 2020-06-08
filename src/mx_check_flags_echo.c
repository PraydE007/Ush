#include "../inc/ush.h"

static t_echo *create_echo(void) {
    t_echo *flags = (t_echo *)malloc(sizeof(t_echo));

    flags->E = false;
    flags->n = false;
    return flags;
}

static void merge_echo(t_echo *src, t_echo *dst) {
    if (!(src->n))
        src->n = dst->n;
    src->E = dst->E;
}

static bool check_flags(t_echo *flags, char *str) {
    t_echo *rez = create_echo();
    int len = mx_strlen(str);

    for (int i = 1; i < len; i++) {
        if (str[i] == 'n')
            rez->n = true;
        else if (str[i] == 'E')
            rez->E = true;
        else if (str[i] == 'e')
            rez->E = false;
        else {
            free(rez);
            return false;
        }
    }
    merge_echo(flags, rez);
    free(rez);
    return true;
}

t_echo *mx_check_flags_echo(char **arr, int *piv) {
    t_echo *flags = create_echo();
    int i = 1;

    while (arr[i]) {
        if (arr[i][0] == '-') {
            if (!check_flags(flags, arr[i]))
                break;
        }
        else
            break;
        i++;
    }
    (*piv) = i;
    return flags;
}
