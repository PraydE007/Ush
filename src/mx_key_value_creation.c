#include "../inc/ush.h"

char **mx_key_value_creation(t_ush *ush, char *env) {
    char **kv = NULL;

    if (mx_have_equals(ush, env)) {
        kv = mx_strsplit(env, '=');
    }
    return kv;
}
