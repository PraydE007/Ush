#include "../inc/ush.h"

static void serial_number_setting(t_jobs **list, t_jobs **pl_jobs) {
    t_jobs *pl_jobs2 = *list;
    int lenth = mx_jobs_list_len(list);
    // while (pl2) {
    //     if (pl2->serial_number > (*pl)->serial_number)
    //             pl2->serial_number = pl2->serial_number - 1;
    //     pl2 = pl2->next;
    // }
    while (pl_jobs2) {
        if (pl_jobs2->serial_number > (*pl_jobs)->serial_number)
            pl_jobs2->serial_number = pl_jobs2->serial_number - 1;
        if (pl_jobs2->sign == '+')
            pl_jobs2->sign = '-';
        else if (pl_jobs2->sign == '-')
            pl_jobs2->sign = ' ';
        pl_jobs2 = pl_jobs2->next;
    }
    (*pl_jobs)->sign = '+';
    (*pl_jobs)->serial_number = lenth;
}
