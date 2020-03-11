#include "../inc/ush.h"

t_env_flags *mx_create_env_flags(void) {
    t_env_flags *flags = (t_env_flags *)malloc(sizeof(t_env_flags));

    flags->i = 0;
    flags->P = 0;
    flags->u = 0;
    return flags;
}
