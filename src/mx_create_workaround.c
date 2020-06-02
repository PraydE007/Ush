#include "../inc/ush.h"

t_wa *mx_create_workaround(t_ush *ush) {
    t_wa *wa = (t_wa *)malloc(sizeof(t_wa));

    wa->buf = NULL;
    wa->p_b = NULL;
    wa->ush = ush;
    return wa;
}
