#include "../inc/ush.h"

static bool is_plus_sign_change(t_jobs **list, int index) {
    t_jobs *pl = *list;

    while (pl->next) {
        if (pl->number == index)
            break;
        pl = pl->next;
    }
    if (pl->sign == '+')
        return true;
    return false;
}

static bool is_minus_sign_change(t_jobs **list, int index) {
    t_jobs *pl = *list;

    while (pl->next) {
        if (pl->number == index)
            break;
        pl = pl->next;
    }
    if (pl->sign == '-')
        return true;
    return false;
}

static void plus_sign_change(t_jobs **list, int size) {
    t_jobs *pl = *list;

    while (pl) {
        if (pl->sign == '-')
            pl->sign = '+';
        else if (pl->serial_number == size - 2)
            pl->sign = '-';
        // else if (size == 2 && pl->sign == ' ')
        //     pl->sign = '-';
        pl = pl->next;
    }
}

static void minus_sign_change(t_jobs **list, int size) {
    t_jobs *pl = *list;

    while (pl) {
        if (pl->serial_number == size - 2)
            pl->sign = '-';
        pl = pl->next;
    }
}

void mx_jobs_sign_change(t_jobs **list, int index) {
    int size = mx_jobs_list_len(list);

    if ((*list != NULL) && (list != NULL)) {
        if (is_plus_sign_change(list, index))
            plus_sign_change(list, size);
        else if (is_minus_sign_change(list, index))
            minus_sign_change(list, size);
    }
}
